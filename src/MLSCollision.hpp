#pragma once

#include <envire_collision/ODECollision.hpp>
#include <maps/grid/MLSMap.hpp>

#include <iostream>
#include <ode/collision.h>
#include <ode/common.h>
#include <ode/rotation.h>
#include <ode/matrix.h>
#include <ode/odemath.h>
#include <envire_collider_mls/collision_kernel.h>
#include <envire_collider_mls/collision_std.h>
#include <envire_collider_mls/collision_util.h>
#include <envire_collider_mls/config.h>


#define TEMP_RECTANGULAR_BUFFER_ELEMENT_COUNT_ALIGNMENT 1

namespace envire { namespace collision
{

class MLSCollision : public ODECollision<maps::grid::MLSMapKalman>
{
    ENVIRE_ODE_COLLISION_HEADER(MLSCollision)

public:    
    dReal       MinHeight;
    dReal       MaxHeight;    
    dReal       widthX;
    dReal       widthY;  
    dReal  		HalfWidthX;
    dReal  		HalfWidthY;  
       
protected:

    void getAABB (dGeomID o, dReal aabb[6], const boost::shared_ptr<maps::grid::MLSMapKalman>& mls);    

    int collide (dGeomID o1, dGeomID o2, int flags, dContactGeom *contact, 
						int skip, const boost::shared_ptr<maps::grid::MLSMapKalman>& mls, int o2_class_id);
	int dCollideSphereMls( const boost::shared_ptr<maps::grid::MLSMapKalman>& mls, 
										   const int minX, const int maxX, const int minZ, const int maxZ, 
                                           dxGeom* o2, const int numMaxContactsPossible,
                                           int flags, dContactGeom* contact, 
                                           int skip );
    dContactGeom   mls_contacts;	

    
    int	WrapMode;           // Heightfield wrapping mode (0=finite, 1=infinite)

};

static inline size_t AlignBufferSize(size_t value, size_t alignment) { dIASSERT((alignment & (alignment - 1)) == 0); 
	return (value + (alignment - 1)) & ~(alignment - 1); }

class MlsFieldVertex
{
public:
    MlsFieldVertex(){};
    dVector3 vertex;
    bool is;    
};

class MlsFieldRectangular
{
public:
    MlsFieldRectangular(){};
    MlsFieldVertex   vertices[4];
};

}}
