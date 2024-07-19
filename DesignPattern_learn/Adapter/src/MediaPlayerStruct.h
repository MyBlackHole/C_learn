#ifndef MEDIA_PLAYER_STRUCT_H_
#define MEDIA_PLAYER_STRUCT_H_

#ifdef __cplusplus
extern "C" {
#endif

struct MediaPlayer {
	void *priv;

	void (*play)(struct MediaPlayer *, const char *audio_type,
		     const char *file_name);
	void (*destroy)(struct MediaPlayer *);
};

#ifdef __cplusplus
}
#endif
#endif // MEDIA_PLAYER_STRUCT_H_
