#include <stdio.h>
#include <stdlib.h>

#include "AdvancedMediaPlayerStruct.h"

static void play_vlc(struct AdvancedMediaPlayer *advanced_media_player,
		     const char *file_name)
{
	printf("Playing vlc file. Name: %s\n", file_name);
}

static void play_mp4(struct AdvancedMediaPlayer *advanced_media_player,
		     const char *file_name)
{
}

struct AdvancedMediaPlayer *vlc_player_create(void)
{
	struct AdvancedMediaPlayer *player =
		(struct AdvancedMediaPlayer *)calloc(
			1, sizeof(struct AdvancedMediaPlayer));
	player->play_mp4 = play_mp4;
	player->play_vlc = play_vlc;

	return player;
}
