/**
 * @file zfs-tools.h
 * @author yezi (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __ZFS_TOOLS_H__
#define __ZFS_TOOLS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdtypes.h"
#include "param.h"
#include "sysmacros.h"

#include <stdint.h>

enum { ZFS_STREAM_COMPLETED = 0x7fffffff };

#define ZIO_OBJSET_MAC_LEN 32
#define ZIO_DATA_IV_LEN 12
#define ZIO_DATA_SALT_LEN 8
#define ZIO_DATA_MAC_LEN 16

#define DRR_OBJECT_PAYLOAD_SIZE(drro)                               \
	((drro)->drr_raw_bonuslen != 0 ? (drro)->drr_raw_bonuslen : \
					 P2ROUNDUP((drro)->drr_bonuslen, 8))

#define DRR_SPILL_PAYLOAD_SIZE(drrs)                                 \
	((drrs)->drr_compressed_size ? (drrs)->drr_compressed_size : \
				       (drrs)->drr_length)

#define DRR_WRITE_COMPRESSED(drrw) ((drrw)->drr_compressiontype != 0)
#define DRR_WRITE_PAYLOAD_SIZE(drrw)                                \
	(DRR_WRITE_COMPRESSED(drrw) ? (drrw)->drr_compressed_size : \
				      (drrw)->drr_logical_size)

typedef enum dmu_object_byteswap {
	DMU_BSWAP_UINT8,
	DMU_BSWAP_UINT16,
	DMU_BSWAP_UINT32,
	DMU_BSWAP_UINT64,
	DMU_BSWAP_ZAP,
	DMU_BSWAP_DNODE,
	DMU_BSWAP_OBJSET,
	DMU_BSWAP_ZNODE,
	DMU_BSWAP_OLDACL,
	DMU_BSWAP_ACL,
	/*
	 * Allocating a new byteswap type number makes the on-disk format
	 * incompatible with any other format that uses the same number.
	 *
	 * Data can usually be structured to work with one of the
	 * DMU_BSWAP_UINT* or DMU_BSWAP_ZAP types.
	 */
	DMU_BSWAP_NUMFUNCS
} dmu_object_byteswap_t;

#define DMU_OT_NEWTYPE 0x80
#define DMU_OT_METADATA 0x40
#define DMU_OT_ENCRYPTED 0x20
#define DMU_OT_BYTESWAP_MASK 0x1f

#define DMU_OT(byteswap, metadata, encrypted)                  \
	(DMU_OT_NEWTYPE | ((metadata) ? DMU_OT_METADATA : 0) | \
	 ((encrypted) ? DMU_OT_ENCRYPTED : 0) |                \
	 ((byteswap) & DMU_OT_BYTESWAP_MASK))

typedef enum dmu_object_type {
	DMU_OT_NONE,
	/* general: */
	DMU_OT_OBJECT_DIRECTORY, /* ZAP */
	DMU_OT_OBJECT_ARRAY, /* UINT64 */
	DMU_OT_PACKED_NVLIST, /* UINT8 (XDR by nvlist_pack/unpack) */
	DMU_OT_PACKED_NVLIST_SIZE, /* UINT64 */
	DMU_OT_BPOBJ, /* UINT64 */
	DMU_OT_BPOBJ_HDR, /* UINT64 */
	/* spa: */
	DMU_OT_SPACE_MAP_HEADER, /* UINT64 */
	DMU_OT_SPACE_MAP, /* UINT64 */
	/* zil: */
	DMU_OT_INTENT_LOG, /* UINT64 */
	/* dmu: */
	DMU_OT_DNODE, /* DNODE */
	DMU_OT_OBJSET, /* OBJSET */
	/* dsl: */
	DMU_OT_DSL_DIR, /* UINT64 */
	DMU_OT_DSL_DIR_CHILD_MAP, /* ZAP */
	DMU_OT_DSL_DS_SNAP_MAP, /* ZAP */
	DMU_OT_DSL_PROPS, /* ZAP */
	DMU_OT_DSL_DATASET, /* UINT64 */
	/* zpl: */
	DMU_OT_ZNODE, /* ZNODE */
	DMU_OT_OLDACL, /* Old ACL */
	DMU_OT_PLAIN_FILE_CONTENTS, /* UINT8 */
	DMU_OT_DIRECTORY_CONTENTS, /* ZAP */
	DMU_OT_MASTER_NODE, /* ZAP */
	DMU_OT_UNLINKED_SET, /* ZAP */
	/* zvol: */
	DMU_OT_ZVOL, /* UINT8 */
	DMU_OT_ZVOL_PROP, /* ZAP */
	/* other; for testing only! */
	DMU_OT_PLAIN_OTHER, /* UINT8 */
	DMU_OT_UINT64_OTHER, /* UINT64 */
	DMU_OT_ZAP_OTHER, /* ZAP */
	/* new object types: */
	DMU_OT_ERROR_LOG, /* ZAP */
	DMU_OT_SPA_HISTORY, /* UINT8 */
	DMU_OT_SPA_HISTORY_OFFSETS, /* spa_his_phys_t */
	DMU_OT_POOL_PROPS, /* ZAP */
	DMU_OT_DSL_PERMS, /* ZAP */
	DMU_OT_ACL, /* ACL */
	DMU_OT_SYSACL, /* SYSACL */
	DMU_OT_FUID, /* FUID table (Packed NVLIST UINT8) */
	DMU_OT_FUID_SIZE, /* FUID table size UINT64 */
	DMU_OT_NEXT_CLONES, /* ZAP */
	DMU_OT_SCAN_QUEUE, /* ZAP */
	DMU_OT_USERGROUP_USED, /* ZAP */
	DMU_OT_USERGROUP_QUOTA, /* ZAP */
	DMU_OT_USERREFS, /* ZAP */
	DMU_OT_DDT_ZAP, /* ZAP */
	DMU_OT_DDT_STATS, /* ZAP */
	DMU_OT_SA, /* System attr */
	DMU_OT_SA_MASTER_NODE, /* ZAP */
	DMU_OT_SA_ATTR_REGISTRATION, /* ZAP */
	DMU_OT_SA_ATTR_LAYOUTS, /* ZAP */
	DMU_OT_SCAN_XLATE, /* ZAP */
	DMU_OT_DEDUP, /* fake dedup BP from ddt_bp_create() */
	DMU_OT_DEADLIST, /* ZAP */
	DMU_OT_DEADLIST_HDR, /* UINT64 */
	DMU_OT_DSL_CLONES, /* ZAP */
	DMU_OT_BPOBJ_SUBOBJ, /* UINT64 */
	/*
	 * Do not allocate new object types here. Doing so makes the on-disk
	 * format incompatible with any other format that uses the same object
	 * type number.
	 *
	 * When creating an object which does not have one of the above types
	 * use the DMU_OTN_* type with the correct byteswap and metadata
	 * values.
	 *
	 * The DMU_OTN_* types do not have entries in the dmu_ot table,
	 * use the DMU_OT_IS_METADATA() and DMU_OT_BYTESWAP() macros instead
	 * of indexing into dmu_ot directly (this works for both DMU_OT_* types
	 * and DMU_OTN_* types).
	 */
	DMU_OT_NUMTYPES,

	/*
	 * Names for valid types declared with DMU_OT().
	 */
	DMU_OTN_UINT8_DATA = DMU_OT(DMU_BSWAP_UINT8, B_FALSE, B_FALSE),
	DMU_OTN_UINT8_METADATA = DMU_OT(DMU_BSWAP_UINT8, B_TRUE, B_FALSE),
	DMU_OTN_UINT16_DATA = DMU_OT(DMU_BSWAP_UINT16, B_FALSE, B_FALSE),
	DMU_OTN_UINT16_METADATA = DMU_OT(DMU_BSWAP_UINT16, B_TRUE, B_FALSE),
	DMU_OTN_UINT32_DATA = DMU_OT(DMU_BSWAP_UINT32, B_FALSE, B_FALSE),
	DMU_OTN_UINT32_METADATA = DMU_OT(DMU_BSWAP_UINT32, B_TRUE, B_FALSE),
	DMU_OTN_UINT64_DATA = DMU_OT(DMU_BSWAP_UINT64, B_FALSE, B_FALSE),
	DMU_OTN_UINT64_METADATA = DMU_OT(DMU_BSWAP_UINT64, B_TRUE, B_FALSE),
	DMU_OTN_ZAP_DATA = DMU_OT(DMU_BSWAP_ZAP, B_FALSE, B_FALSE),
	DMU_OTN_ZAP_METADATA = DMU_OT(DMU_BSWAP_ZAP, B_TRUE, B_FALSE),

	DMU_OTN_UINT8_ENC_DATA = DMU_OT(DMU_BSWAP_UINT8, B_FALSE, B_TRUE),
	DMU_OTN_UINT8_ENC_METADATA = DMU_OT(DMU_BSWAP_UINT8, B_TRUE, B_TRUE),
	DMU_OTN_UINT16_ENC_DATA = DMU_OT(DMU_BSWAP_UINT16, B_FALSE, B_TRUE),
	DMU_OTN_UINT16_ENC_METADATA = DMU_OT(DMU_BSWAP_UINT16, B_TRUE, B_TRUE),
	DMU_OTN_UINT32_ENC_DATA = DMU_OT(DMU_BSWAP_UINT32, B_FALSE, B_TRUE),
	DMU_OTN_UINT32_ENC_METADATA = DMU_OT(DMU_BSWAP_UINT32, B_TRUE, B_TRUE),
	DMU_OTN_UINT64_ENC_DATA = DMU_OT(DMU_BSWAP_UINT64, B_FALSE, B_TRUE),
	DMU_OTN_UINT64_ENC_METADATA = DMU_OT(DMU_BSWAP_UINT64, B_TRUE, B_TRUE),
	DMU_OTN_ZAP_ENC_DATA = DMU_OT(DMU_BSWAP_ZAP, B_FALSE, B_TRUE),
	DMU_OTN_ZAP_ENC_METADATA = DMU_OT(DMU_BSWAP_ZAP, B_TRUE, B_TRUE),
} dmu_object_type_t;

typedef enum dmu_objset_type {
	DMU_OST_NONE,
	DMU_OST_META,
	DMU_OST_ZFS,
	DMU_OST_ZVOL,
	DMU_OST_OTHER, /* For testing only! */
	DMU_OST_ANY, /* Be careful! */
	DMU_OST_NUMTYPES
} dmu_objset_type_t;

typedef struct zio_cksum {
	uint64_t zc_word[4];
} zio_cksum_t;

typedef struct ddt_key {
	zio_cksum_t ddk_cksum; /* 256-bit block checksum */
	/*
	 * Encoded with logical & physical size, encryption, and compression,
	 * as follows:
	 *   +-------+-------+-------+-------+-------+-------+-------+-------+
	 *   |   0   |   0   |   0   |X| comp|     PSIZE     |     LSIZE     |
	 *   +-------+-------+-------+-------+-------+-------+-------+-------+
	 */
	uint64_t ddk_prop;
} ddt_key_t;

struct drr_begin {
	uint64_t drr_magic;
	uint64_t drr_versioninfo; /* was drr_version */
	uint64_t drr_creation_time;
	dmu_objset_type_t drr_type;
	uint32_t drr_flags;
	uint64_t drr_toguid;
	uint64_t drr_fromguid;
	char drr_toname[MAXNAMELEN];
};

typedef struct dmu_replay_record {
	enum {
		DRR_BEGIN,
		DRR_OBJECT,
		DRR_FREEOBJECTS,
		DRR_WRITE,
		DRR_FREE,
		DRR_END,
		DRR_WRITE_BYREF,
		DRR_SPILL,
		DRR_WRITE_EMBEDDED,
		DRR_OBJECT_RANGE,
		DRR_REDACT,
		DRR_NUMTYPES
	} drr_type;
	uint32_t drr_payloadlen;
	union {
		struct drr_begin drr_begin;
		struct drr_end {
			zio_cksum_t drr_checksum;
			uint64_t drr_toguid;
		} drr_end;
		struct drr_object {
			uint64_t drr_object;
			dmu_object_type_t drr_type;
			dmu_object_type_t drr_bonustype;
			uint32_t drr_blksz;
			uint32_t drr_bonuslen;
			uint8_t drr_checksumtype;
			uint8_t drr_compress;
			uint8_t drr_dn_slots;
			uint8_t drr_flags;
			uint32_t drr_raw_bonuslen;
			uint64_t drr_toguid;
			/* only (possibly) nonzero for raw streams */
			uint8_t drr_indblkshift;
			uint8_t drr_nlevels;
			uint8_t drr_nblkptr;
			uint8_t drr_pad[5];
			uint64_t drr_maxblkid;
			/* bonus content follows */
		} drr_object;
		struct drr_freeobjects {
			uint64_t drr_firstobj;
			uint64_t drr_numobjs;
			uint64_t drr_toguid;
		} drr_freeobjects;
		struct drr_write {
			uint64_t drr_object;
			dmu_object_type_t drr_type;
			uint32_t drr_pad;
			uint64_t drr_offset;
			uint64_t drr_logical_size;
			uint64_t drr_toguid;
			uint8_t drr_checksumtype;
			uint8_t drr_flags;
			uint8_t drr_compressiontype;
			uint8_t drr_pad2[5];
			/* deduplication key */
			ddt_key_t drr_key;
			/* only nonzero if drr_compressiontype is not 0 */
			uint64_t drr_compressed_size;
			/* only nonzero for raw streams */
			uint8_t drr_salt[ZIO_DATA_SALT_LEN];
			uint8_t drr_iv[ZIO_DATA_IV_LEN];
			uint8_t drr_mac[ZIO_DATA_MAC_LEN];
			/* content follows */
		} drr_write;
		struct drr_free {
			uint64_t drr_object;
			uint64_t drr_offset;
			uint64_t drr_length;
			uint64_t drr_toguid;
		} drr_free;
		struct drr_write_byref {
			/* where to put the data */
			uint64_t drr_object;
			uint64_t drr_offset;
			uint64_t drr_length;
			uint64_t drr_toguid;
			/* where to find the prior copy of the data */
			uint64_t drr_refguid;
			uint64_t drr_refobject;
			uint64_t drr_refoffset;
			/* properties of the data */
			uint8_t drr_checksumtype;
			uint8_t drr_flags;
			uint8_t drr_pad2[6];
			ddt_key_t drr_key; /* deduplication key */
		} drr_write_byref;
		struct drr_spill {
			uint64_t drr_object;
			uint64_t drr_length;
			uint64_t drr_toguid;
			uint8_t drr_flags;
			uint8_t drr_compressiontype;
			uint8_t drr_pad[6];
			/* only nonzero for raw streams */
			uint64_t drr_compressed_size;
			uint8_t drr_salt[ZIO_DATA_SALT_LEN];
			uint8_t drr_iv[ZIO_DATA_IV_LEN];
			uint8_t drr_mac[ZIO_DATA_MAC_LEN];
			dmu_object_type_t drr_type;
			/* spill data follows */
		} drr_spill;
		struct drr_write_embedded {
			uint64_t drr_object;
			uint64_t drr_offset;
			/* logical length, should equal blocksize */
			uint64_t drr_length;
			uint64_t drr_toguid;
			uint8_t drr_compression;
			uint8_t drr_etype;
			uint8_t drr_pad[6];
			uint32_t drr_lsize; /* uncompressed size of payload */
			uint32_t drr_psize; /* compr. (real) size of payload */
			/* (possibly compressed) content follows */
		} drr_write_embedded;
		struct drr_object_range {
			uint64_t drr_firstobj;
			uint64_t drr_numslots;
			uint64_t drr_toguid;
			uint8_t drr_salt[ZIO_DATA_SALT_LEN];
			uint8_t drr_iv[ZIO_DATA_IV_LEN];
			uint8_t drr_mac[ZIO_DATA_MAC_LEN];
			uint8_t drr_flags;
			uint8_t drr_pad[3];
		} drr_object_range;
		struct drr_redact {
			uint64_t drr_object;
			uint64_t drr_offset;
			uint64_t drr_length;
			uint64_t drr_toguid;
		} drr_redact;

		/*
		 * Note: drr_checksum is overlaid with all record types
		 * except DRR_BEGIN.  Therefore its (non-pad) members
		 * must not overlap with members from the other structs.
		 * We accomplish this by putting its members at the very
		 * end of the struct.
		 */
		struct drr_checksum {
			uint64_t drr_pad[34];
			/*
			 * fletcher-4 checksum of everything preceding the
			 * checksum.
			 */
			zio_cksum_t drr_checksum;
		} drr_checksum;
	} drr_u;
} dmu_replay_record_t;

#ifdef __cplusplus
}
#endif

#endif /**__ZFS_TOOLS_H__**/
