#include "Background.h"

typedef char string[150];

typedef enum {spa,sapa,srl,srls} society;

typedef struct {
    string Name;
    float Found;
    society type; 
} Company;

