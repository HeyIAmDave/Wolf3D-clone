#pragma once

class Scene
{
public:
	Scene()
		: contentLoaded(false)
	{}
	virtual ~Scene() {}

	virtual void OnLoadContent() = 0;
	virtual void OnUnloadContent() = 0;
	virtual void OnUpdate(float delta) = 0;
	virtual void OnRender() = 0;

	inline bool HasLoadedContent() const { return contentLoaded; }
protected:
	std::atomic_bool contentLoaded;
};