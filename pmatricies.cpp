#include "pmatricies.h"

/*
 * Includes glprojection matrix and opencv projection matrix.
 * Open cv projection matrix needs for calculating marker position.
 * glprojection matrix and opencv proejction matrix needs to be in syncron.
 * It means cvmatrix needs to be recalculated when the image size changes
 * cv matrix depends on image size
 * by Nandor
 * **/

Pmatricies::Pmatricies()
{
}
