//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is licensed  under the terms of the GNU General Public License v3.0.
//  See the attached LICENSE.txt file or https://www.gnu.org/licenses/gpl-3.0.en.html.
//  This notice and the license may not be removed or altered from any source distribution.

#include <core/Entity/Entity.h>

#include <obj/Indexer.h>
#include <math/Timer.h>
#include <math/Math.h>

#include <core/World/World.h>

#include <core/World/Section.h>

#include <proto/Proto.h>

#include <refl/Meta.h>

using namespace mud; namespace toy
{
	Spatial::Spatial(Entity& entity, World& world, HSpatial parent, const vec3& position, const quat& rotation)
        : Transform(position, rotation, Unit3)
		, m_entity(&entity)
		, m_world(&world)
		, m_parent(parent)
		, m_hooked(true)
	{}

	Spatial::Spatial(Entity& entity, HSpatial parent, const vec3& position, const quat& rotation)
		: Spatial(entity, *parent->m_world, parent, position, rotation)
	{}

    Spatial::~Spatial()
    {}

	Spatial& Spatial::origin()
	{
		return m_world->origin();
	}

	void Spatial::debug_contents(size_t depth)
	{
		if(m_contents.size() > 1)
		{
			for(size_t o = 0; o < depth; ++o)
				printf("    ");

			printf("Spatial %u : %zu leafs\n", 0U, m_contents.size());
		}

		for(HSpatial child : m_contents)
			child->debug_contents(depth + 1);
	}

	vec3 Spatial::absolute_position() const
	{
		if(m_parent)
			return m_position + m_parent->absolute_position();
		else
			return m_position;
	}

	quat Spatial::absolute_rotation() const
	{
		if(m_parent)
			return m_rotation * m_parent->absolute_rotation();
		else
			return m_rotation;
	}

	void Spatial::translate(const vec3& vec)
	{
		set_position(mud::rotate(m_rotation, vec) + m_position);
	}

	void Spatial::rotate(const vec3& axis, float angle)
	{
		quat rot = angle_axis(angle, mud::rotate(m_rotation, axis));
		set_rotation(rot * m_rotation);
		normalize(m_rotation);
	}

	void Spatial::yaw(float value)
	{
		vec3 axis(glm::rotate(m_rotation, Y3));			
		rotate(axis, value);
	}

	void Spatial::yaw_fixed(float value)
	{			
		rotate(Y3, value);
	}

	void Spatial::pitch(float value)
	{
		vec3 axis(glm::rotate(m_rotation, X3));
		rotate(axis, value);
	}

	void Spatial::roll(float value)
	{
		vec3 axis(glm::rotate(m_rotation, Z3));
		rotate(axis, value);
	}

    void Spatial::next_frame(size_t tick, size_t delta)
    {
		UNUSED(delta);

		m_moved = false;
		m_last_tick = tick;
	}

	void Spatial::hook()
	{
		m_hooked = true;
	}

	void Spatial::unhook()
	{
		m_hooked = false;
	}

	bool Spatial::is_child_of(Spatial& spatial)
	{
		if(&(*m_parent) == &spatial)
			return true;
		else if(m_parent)
			return m_parent->is_child_of(spatial);
		else
			return false;
	}

	Spatial* Spatial::spatial_root()
	{
		if(m_parent)
			return m_parent->spatial_root();
		else
			return this;
	}

	void Spatial::detach(Spatial& child)
	{
		child.m_parent = 0;
		//vector_remove(m_contents, child);
	}

	void Spatial::visit(const Visitor& visitor)
	{
		if(!visitor(*this))
			return;

		for(HSpatial spatial : m_contents)
			spatial->visit(visitor);
	}

	void detach_to(HSpatial self, HSpatial target)
	{
		Spatial& spatial = self;
		Spatial& movefrom = spatial.m_parent;
		spatial.m_parent = target;
		vector_remove(movefrom.m_contents, self);
		target->m_contents.push_back(self);
		spatial.set_dirty(false);
	}

	void set_parent(HSpatial self, HSpatial target)
	{
		detach_to(self, target);
	}
}
