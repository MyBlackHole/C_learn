struct DrawAPI {
	void *priv;

	void (*draw_circle)(struct DrawAPI *, int radius, int x, int y);
	void (*destroy)(struct DrawAPI *);
};
