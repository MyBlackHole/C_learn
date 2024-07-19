#ifndef COMPOSITE_ENTITY_H_
#define COMPOSITE_ENTITY_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CompositeEntity CompositeEntity;

CompositeEntity *composite_entity_create(void);

void composite_entity_destroy(CompositeEntity **composite_entity);

void composite_entity_set_data(CompositeEntity *composite_entity,
			       const char *data1, const char *data2);

const char **composite_entity_get_data(CompositeEntity *composite_entity,
				       int *data_length);

#ifdef __cplusplus
}
#endif
#endif // COMPOSITE_ENTITY_H_
