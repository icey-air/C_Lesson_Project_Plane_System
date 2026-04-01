#ifndef __DATAFILE_H
#define __DATAFILE_H

#include "plane.h"
#include "tourist.h"

#define PLANE_DATA_FILE "plane_data.dat"
#define TOURIST_DATA_FILE "tourist_data.dat"

int SavePlaneData(Plane_information* head);
int LoadPlaneData(Plane_information** head);
int SaveAllTourists(struct tourist* head);
int LoadAllTourists(struct tourist** head, struct Plane_information* planeHead);

#endif