#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
/******************************************************************************/
#include "entity_component.h"
#include "types.h"
#include <vector>
/******************************************************************************/
class EntityManager{
/******************************************************************************/
    public:
	EntityManager(){
	    ents.clear();

	    // probably best to resize these initially vs. clear() [makes size=0]
	    // comps_pos.clear();
	    // comps_vel.clear();
	    pos.resize(5);
	    vel.resize(5);
	    rendpos.resize(5);
	    texture.resize(5);
	}
/******************************************************************************/
    public:
	~EntityManager(){
	    // std::cerr << "Entities count: " << ents.size() << std::endl;
	    // for(i16 i=0; i<ents.size(); ++i){

		// if((ents[i]&(CM_POS|CM_VEL))==(CM_POS|CM_VEL)){
		//     std::cerr << "ent[" <<i<<"] x: " << pos[i].x << " y: " << pos[i].y << std::endl;
		//     if(ents[i]&CM_RENDPOS){
		// 	std::cerr<<"rendpos_x: "<<rendpos[i].x<<" rendpos_y: " <<rendpos[i].y<<std::endl;
		//     }
		//     else { std::cerr<<"-No CM_RENDPOS"<<std::endl; }
		// }
		// if(ents[i]&CM_TEXTURE){
		//     std::cerr << "entity["<<i<<"] has CM_TEXTURE" << std::endl;
		// }
	    // }
	}
/******************************************************************************/
    public:
	rt add_entity(ui64 comp_mask);
	//TODO:
	//rt del_entity(i16 id);
	//rt add_comp(i16 ownid, ENTITY_COMPONENT comp)
	//rt del_comp(i16 ownid, ENTITY_COMPONENT comp)
/******************************************************************************/
    public:
	std::vector<ui64> ents;
	std::vector<cPos> pos;
	std::vector<cVel> vel;
	std::vector<cRendPos> rendpos;
	std::vector<cTexture> texture;
/******************************************************************************/
    public:
	// rt set(PP pp);
	rt set(EC& pec);
/******************************************************************************/
	// rt set_pos(i16 own_id, float px, float py, float pw, float ph);
	// rt set_rendpos(i16 own_id, float px, float py, float pw, float ph);
	// rt set_vel(i16 own_id, float px, float py);
	// rt set_texture(i16 own_id, i16 renderer_index, i16 texture_index);
};
/******************************************************************************/
#endif
/******************************************************************************/

