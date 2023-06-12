#include "Physics2D.h"

bool Physics2D::CollisionDetection() {
	for (int i = 0; i < physics_entities.size()-1; ++i) {
		for (int j = i+1; j < physics_entities.size(); ++j) {
			if (physics_entities.at(i)->getColliderName() == "box collider"
				&& physics_entities.at(j)->getColliderName() == "box collider") {
				if (box_box_collision(dynamic_cast<BoxCollider*>(physics_entities[i]),
					dynamic_cast<BoxCollider*>(physics_entities[j]))) {
					if (physics_entities[i]->isCollided == false
						&& physics_entities[j]->isCollided == false) {
						collision_pair = { physics_entities[i]->parent, physics_entities[j]->parent };
						return true;
					}
				}
			}
			else if (physics_entities.at(i)->getColliderName() == "circle collider"
				&& physics_entities.at(j)->getColliderName() == "circle collider") {
				if (circle_circle_collision(dynamic_cast<CircleCollider*>(physics_entities[i]),
					dynamic_cast<CircleCollider*>(physics_entities[j]))) {
					if (physics_entities[i]->isCollided == false) {
						physics_entities[i]->isCollided = true;
						physics_entities[j]->isCollided = true;
						collision_pair = { physics_entities[i]->parent, physics_entities[j]->parent };
						return true;
					}
				}
			}
			else if (physics_entities.at(i)->getColliderName() == "box collider"
				&& physics_entities.at(j)->getColliderName() == "circle collider") {
				if (box_circle_collision(dynamic_cast<BoxCollider*>(physics_entities[i]),
					dynamic_cast<CircleCollider*>(physics_entities[j]))) {
					if (physics_entities[i]->isCollided == false) {
						physics_entities[i]->isCollided = true;
						physics_entities[j]->isCollided = true;
						collision_pair = { physics_entities[i]->parent, physics_entities[j]->parent };
						return true;
					}
				}
			}
			else if (physics_entities.at(i)->getColliderName() == "circle collider"
				&& physics_entities.at(j)->getColliderName() == "box collider") {
				if (box_circle_collision(dynamic_cast<BoxCollider*>(physics_entities[j]),
					dynamic_cast<CircleCollider*>(physics_entities[i]))) {
					if (physics_entities[j]->isCollided == false) {
						physics_entities[i]->isCollided = true;
						physics_entities[j]->isCollided = true;
						collision_pair = { physics_entities[i]->parent, physics_entities[j]->parent };
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Physics2D::box_box_collision(BoxCollider* box1, BoxCollider* box2) {
	return BoxCollider::isCollided(box1, box2);
}

bool Physics2D::circle_circle_collision(CircleCollider* circle1, CircleCollider* circle2) {
	return CircleCollider::isCollided(circle1, circle2);
}

bool Physics2D::box_circle_collision(BoxCollider* box, CircleCollider* circle) {
	// find the closest point on the box to the circle
	float closest_x = max(XMVectorGetX(box->position) - box->getHalfLength(),
		min(XMVectorGetX(circle->position), XMVectorGetX(box->position) + box->getHalfLength()));
	float closest_y = max(XMVectorGetY(box->position) - box->getHalfLength(),
		min(XMVectorGetY(circle->position), XMVectorGetY(box->position) + box->getHalfLength()));
	// Calculate the distance between the closest point and the circle's center
	float distance_x = XMVectorGetX(circle->position) - closest_x;
	float distance_y = XMVectorGetY(circle->position) - closest_y;
	float distance = sqrt(distance_x * distance_x + distance_y * distance_y);
	// Check if the distance is less than or equal to the circle's radius
	if (distance <= circle->getRadius()) {
		return true;
	}
	else    return false;
}