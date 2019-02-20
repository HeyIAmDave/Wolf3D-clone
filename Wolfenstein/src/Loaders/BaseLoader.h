#pragma once

template<class T>
class BaseLoader
{
public:
	virtual ~BaseLoader() {}

	virtual T& Load(const std::string& fileName) = 0;

	inline void CleanUp()
	{
		for (auto& obj : m_list)
			obj.second->CleanUp();

		m_list.clear();
	}
protected:
	std::unordered_map<std::string, std::shared_ptr<T>> m_list;
};