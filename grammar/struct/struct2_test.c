#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Line {
	uint32_t length;

	// 以下两属性共用内存空间
	uint8_t contents[0];
	uint8_t data[];
};

struct Line2 {
	uint32_t length;

	// 以下两属性共用内存空间
	uint8_t contents[10];
};

struct ObBackupCommonHeader {
	uint8_t COMMON_HEADER_VERSION;
	uint8_t MACRO_DATA_HEADER_VERSION;
	uint16_t data_type_;
	uint16_t header_version_; // header version
	uint16_t data_version_;
	uint16_t compressor_type_; // data compression type
	int16_t header_length_; // = sizeof(ObBackupCommonHeader)
	int16_t header_checksum_;
	int64_t data_length_; // length of data before compression
	int64_t data_zlength_; // length of data after compression
	int64_t data_checksum_; // checksum of data part
	int64_t align_length_;
};

enum STATUS {
	INVALID = 0,
	STOP = 1,
	BEGINNING = 2,
	DOING = 3,
	STOPPING = 4,
	INTERRUPTED = 5,
	MIXED = 6,
	PAUSED = 7, // only used for backup backup log archive
	MAX
};

struct ObTenantLogArchiveStatus {
	uint64_t tenant_id_;
	int64_t copy_id_;
	int64_t start_ts_;
	int64_t checkpoint_ts_;
	int64_t incarnation_;
	int64_t round_;
	enum STATUS status_;
	// bool is_mark_deleted_;
	// bool is_mount_file_created_;  // used to check if backup dest is mount
	// properly
	int64_t compatible_;
	int64_t backup_piece_id_;
	int64_t start_piece_id_;
};

int demo_struct2_main()
{
	struct Line line;
	int length = 100;

	struct Line2 line2;

	printf("line: %ld\n", sizeof(line));
	printf("line2: %ld\n", sizeof(line2));
	printf("ObBackupCommonHeader %ld\n",
	       sizeof(struct ObBackupCommonHeader));
	printf("ObTenantLogArchiveStatus %ld\n",
	       sizeof(struct ObTenantLogArchiveStatus));

	struct Line *line_ptr =
		(struct Line *)malloc(sizeof(struct Line) + length);
	// 代表 contents 100 char
	line_ptr->length = 100;
	line_ptr->contents[96] = 100;
	printf("contents: %d\n", line_ptr->contents[96]);
	printf("data: %d\n", line_ptr->data[96]);
	return EXIT_SUCCESS;
}

// OUTPUT:
// line: 4
// line2: 16
// ObBackupCommonHeader 48
// ObTenantLogArchiveStatus 80
// contents: 100
// data: 100
