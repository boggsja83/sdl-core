#include "entity_manager.h"
#include "types.h"

rt EntityManager::add_entity(uint64_t comp_mask){
    int16_t temp_id = entities.size();

    entities.push_back(comp_mask);

    if( (comp_mask & CM_POS) == CM_POS ){
	comp_pos.push_back( cPos(temp_id) );
	// comp_pos.emplace_back( cPos(temp_id, 69, 69, 420, 420) );
    }

    return OKAY;
}

