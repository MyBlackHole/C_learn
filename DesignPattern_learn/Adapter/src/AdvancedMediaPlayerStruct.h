#ifndef ADVANCED_MEDIA_PLAYER_STRUCT_H_
#define ADVANCED_MEDIA_PLAYER_STRUCT_H_

#ifdef __cplusplus
extern "C" {
#endif

struct AdvancedMediaPlayer {
	void *priv;

	void (*play_vlc)(struct AdvancedMediaPlayer *, const char *file_name);
	void (*play_mp4)(struct AdvancedMediaPlayer *, const char *file_name);
	void (*destroy)(struct AdvancedMediaPlayer *);
};

#ifdef __cplusplus
}
#endif
#endif // ADVANCED_MEDIA_PLAYER_STRUCT_H_
