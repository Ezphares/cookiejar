#pragma once

#include <foundation/activatable.h>
#include <componentmodel/entity.h>

#include <vector>
#include <map>
#include <list>
#include <memory>

namespace cookiejar
{
	class Behaviour;


	class BehaviourManager : public Activatable<BehaviourManager>
	{
	public:
		BehaviourManager();
		~BehaviourManager();

	public:
		void attach_behaviour(const Entity &entity, std::shared_ptr<Behaviour> behaviour);
		void detach_behaviour(const Entity &entity, std::shared_ptr<Behaviour> behaviour);
		std::vector<std::shared_ptr<Behaviour>> get_behaviours(const Entity &entity);

		void update(float delta);
		void post_update(float delta);

	private:
		std::vector<std::shared_ptr<Behaviour>> _to_init;
		std::vector<Entity> _created, _destroyed;
		std::map<Entity, std::list<std::shared_ptr<Behaviour>>> _behaviours;
	};

}
