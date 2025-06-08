#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef uint64_t XLogRecPtr;
#define LSN_FORMAT_ARGS(lsn) ((uint32_t)((lsn) >> 32)), ((uint32_t)(lsn))

typedef enum DBState {
	DB_STARTUP = 0,
	DB_SHUTDOWNED,
	DB_SHUTDOWNED_IN_RECOVERY,
	DB_SHUTDOWNING,
	DB_IN_CRASH_RECOVERY,
	DB_IN_ARCHIVE_RECOVERY,
	DB_IN_PRODUCTION
} DBState;

typedef struct CheckPoint {
	int64_t redo; /* next RecPtr available when we began to
                                   * create CheckPoint (i.e. REDO start point) */
	uint32_t ThisTimeLineID; /* current TLI */
	bool fullPageWrites; /* current full_page_writes */
	uint64_t nextXid; /* next free XID */
	unsigned int nextOid; /* next free OID */
	uint64_t nextMulti; /* next free MultiXactId */
	uint64_t nextMultiOffset; /* next free MultiXact offset */
	uint64_t oldestXid; /* cluster-wide minimum datfrozenxid */
	uint64_t oldestXidDB; /* database with minimum datfrozenxid */
	int64_t time; /* time stamp of checkpoint */
	uint64_t remove_seg; /*the xlog segno we keep during this checkpoint*/
	/*
     * Oldest XID still running. This is only needed to initialize hot standby
     * mode from an online checkpoint, so we only bother calculating this for
     * online checkpoints and only when wal_level is hot_standby. Otherwise
     * it's set to InvalidTransactionId.
     */
	uint64_t oldestActiveXid;
} CheckPoint;

typedef struct ControlFileData {
	/*
     * Unique system identifier --- to ensure we match up xlog files with the
     * installation that produced them.
     */
	uint64_t system_identifier;

	/*
     * Version identifier information.    Keep these fields at the same offset,
     * especially pg_control_version; they won't be real useful if they move
     * around.    (For historical reasons they must be 8 bytes into the file
     * rather than immediately at the front.)
     *
     * pg_control_version identifies the format of pg_control itself.
     * catalog_version_no identifies the format of the system catalogs.
     *
     * There are additional version identifiers in individual files; for
     * example, WAL logs contain per-page magic numbers that can serve as
     * version cues for the WAL log.
     */
	uint32_t pg_control_version; /* PG_CONTROL_VERSION */
	uint32_t catalog_version_no; /* see catversion.h */
	uint32_t timeline;

	/*
     * System status data
     */
	DBState state; /* see enum above */
	int64_t time; /* time stamp of last pg_control update */
	int64_t checkPoint; /* last check point record ptr */
	int64_t prevCheckPoint; /* previous check point record ptr */

	CheckPoint checkPointCopy; /* copy of last check point record */

	/*
     * These two values determine the minimum point we must recover up to
     * before starting up:
     *
     * minRecoveryPoint is updated to the latest replayed LSN whenever we
     * flush a data change during archive recovery. That guards against
     * starting archive recovery, aborting it, and restarting with an earlier
     * stop location. If we've already flushed data changes from WAL record X
     * to disk, we mustn't start up until we reach X again. Zero when not
     * doing archive recovery.
     *
     * backupStartPoint is the redo pointer of the backup start checkpoint, if
     * we are recovering from an online backup and haven't reached the end of
     * backup yet. It is reset to zero when the end of backup is reached, and
     * we mustn't start up before that. A boolean would suffice otherwise, but
     * we use the redo pointer as a cross-check when we see an end-of-backup
     * record, to make sure the end-of-backup record corresponds the base
     * backup we're recovering from.
     *
     * backupEndPoint is the backup end location, if we are recovering from an
     * online backup which was taken from the standby and haven't reached the
     * end of backup yet. It is initialized to the minimum recovery point in
     * pg_control which was backed up last. It is reset to zero when the end
     * of backup is reached, and we mustn't start up before that.
     *
     * If backupEndRequired is true, we know for sure that we're restoring
     * from a backup, and must see a backup-end record before we can safely
     * start up. If it's false, but backupStartPoint is set, a backup_label
     * file was found at startup but it may have been a leftover from a stray
     * pg_start_backup() call, not accompanied by pg_stop_backup().
     */
	int64_t minRecoveryPoint;
	int64_t backupStartPoint;
	int64_t backupEndPoint;
	bool backupEndRequired;

	/*
     * Parameter settings that determine if the WAL can be used for archival
     * or hot standby.
     */
	int wal_level;
	int MaxConnections;
	int max_prepared_xacts;
	int max_locks_per_xact;

	/*
     * This data is used to check for hardware-architecture compatibility of
     * the database and the backend executable.  We need not check endianness
     * explicitly, since the pg_control version will surely look wrong to a
     * machine of different endianness, but we do need to worry about MAXALIGN
     * and floating-point format.  (Note: storage layout nominally also
     * depends on SHORTALIGN and INTALIGN, but in practice these are the same
     * on all architectures of interest.)
     *
     * Testing just one double value is not a very bulletproof test for
     * floating-point compatibility, but it will catch most cases.
     */
	uint32_t maxAlign; /* alignment requirement for tuples */
	double floatFormat; /* constant 1234567.0 */
#define FLOATFORMAT_VALUE 1234567.0

	/*
     * This data is used to make sure that configuration of this database is
     * compatible with the backend executable.
     */
	uint32_t blcksz; /* data block size for this DB */
	uint32_t relseg_size; /* blocks per segment of large relation */

	uint32_t xlog_blcksz; /* block size within WAL files */
	uint32_t xlog_seg_size; /* size of each WAL segment */

	uint32_t nameDataLen; /* catalog name field width */
	uint32_t indexMaxKeys; /* max number of columns in an index */

	uint32_t toast_max_chunk_size; /* chunk size in TOAST tables */

	/* flag indicating internal format of timestamp, interval, time */
	bool enableIntTimes; /* int64 storage enabled? */

	/* flags indicating pass-by-value status of various types */
	bool float4ByVal; /* float4 pass-by-value? */
	bool float8ByVal; /* float8, int8, etc pass-by-value? */

	/* flag indicating bootstrap relations stored in segment or not */
	bool bootstrap_segment;

	/* CRC of all above ... MUST BE LAST! */
	uint32_t crc;
} ControlFileData;

int main(int argc, char *argv[])
{
	ControlFileData control_data;

	if (argc != 2) {
		printf("Usage: %s pg_control_file_path\n", argv[0]);
		return EXIT_FAILURE;
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		perror("open pg_control failed");
		return EXIT_FAILURE;
	}
	if (read(fd, &control_data, sizeof(ControlFileData)) !=
	    sizeof(ControlFileData)) {
		perror("read pg_control failed");
		return EXIT_FAILURE;
	}
	printf("time: %ld\n", control_data.checkPointCopy.time);
	printf("minRecoveryPoint: %ld\n", control_data.minRecoveryPoint);
	printf("minRecoveryPoint: %X/%X\n",
	       LSN_FORMAT_ARGS(control_data.minRecoveryPoint));
	printf("backupStartPoint: %X/%X\n",
	       LSN_FORMAT_ARGS(control_data.backupStartPoint));
	printf("backupEndPoint: %X/%X\n",
	       LSN_FORMAT_ARGS(control_data.backupEndPoint));
	printf("backupEndRequired: %d\n", control_data.backupEndRequired);
	printf("checkPoint: %X/%X\n",
	       LSN_FORMAT_ARGS(control_data.checkPoint));

	close(fd);
	return EXIT_SUCCESS;
}
