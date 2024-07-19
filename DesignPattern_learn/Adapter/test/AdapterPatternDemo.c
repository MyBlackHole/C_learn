#include "MediaPlayer.h"

int main(int argc, char const *argv[])
{
	MediaPlayer *audio_player = audio_player_create();

	media_player_play(audio_player, "mp3", "beyond the horizon.mp3");
	media_player_play(audio_player, "mp4", "alone.mp4");
	media_player_play(audio_player, "vlc", "far far away.vlc");
	media_player_play(audio_player, "avi", "mind me.avi");

	media_player_destory(&audio_player);
	return 0;
}
