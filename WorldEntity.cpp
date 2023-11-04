#include "WorldEntity.hpp"

bool WorldEntity::IsEnabled() {
	return this->enabled;
}
void WorldEntity::SetEnabled(bool val) {
	enabled = val;
}