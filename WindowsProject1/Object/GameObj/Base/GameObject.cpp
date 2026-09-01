#include "Framework.h"
#include "GameObject.h"

GameObject::GameObject()
: _isActive(false)
, _moveSpeed(0.0f)
, _jumpSpeed(0.0f)
, _isAir(false)
, _movable(true)
, _attackTime(0.0f)
, _maxAttackTime(0.5f)
{
}

void GameObject::CollideProcess()
{
	Vector2 temp;
	_isAir = true;
	_isWall = false;
	int start = (MAPMANAGER->m_terrains.size() - 1) * (_position.x - _oldPos.x < 0);
	int end = (MAPMANAGER->m_terrains.size()) * (_position.x - _oldPos.x >= 0);
	int i = start;
	int move = (_position.x - _oldPos.x >= 0) ? 1 : -1;
	while ((move >= 0 && i < end) || (move < 0 && i >= end))
	{
		if (MAPMANAGER->m_terrains[i]->IsCollision(_oldPos, _position) || MAPMANAGER->m_terrains[i]->FloorCollision(_position))
		{
			if (MAPMANAGER->m_terrains[i]->_direction == LineCollider::DIRECTION::FLOOR)
			{
				if (_jumpSpeed <= 0.0f)
				{
					_jumpSpeed = 0.0f;
					_position = MAPMANAGER->m_terrains[i]->GetCollidePT(_position);
					_isAir = false;
				}
			}
			else
			{
				_position = MAPMANAGER->m_terrains[i]->GetCollidePT(_position);
				_isWall = true;
			}
		}
		i += move;
	}
}
