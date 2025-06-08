#ifndef DRAW_API_H_
#define DRAW_API_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DrawAPI DrawAPI;

DrawAPI *red_circle_create(void);
DrawAPI *green_circle_create(void);
void draw_api_destroy(DrawAPI **draw_api);

#ifdef __cplusplus
}
#endif
#endif // DRAW_API_H_
