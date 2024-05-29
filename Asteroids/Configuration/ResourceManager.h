#pragma once
#include <SFML/Audio/Music.hpp>

#include <unordered_map>
#include <memory>
#include <stdexcept>

template<typename RESOURCE, typename ID = int>
class ResourceManager {
public:
	ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	const ResourceManager& operator=(const ResourceManager&) = delete;

	template<typename ... Args>
	void load(const ID& id, Args&& ... args);

	RESOURCE& get(const ID& id);

private:
	std::unordered_map<ID, std::unique_ptr<RESOURCE>> _map;
};

template<typename RESOURCE, typename ID>
template<typename ...Args>
inline void ResourceManager<RESOURCE, ID>::load(const ID& id, Args && ...args)
{
	auto resource = std::make_unique<RESOURCE>();
	if (!resource->loadFromFile(std::forward<Args>(args) ...)) {
		throw std::runtime_error("Impossible to load file");
	}
	_map.emplace(id, std::move(resource));
}

template<typename RESOURCE, typename ID>
inline RESOURCE& ResourceManager<RESOURCE, ID>::get(const ID& id)
{
	return *_map.at(id);
}

////////////////////////////////

template<typename ID>
class ResourceManager<sf::Music, ID> {
public:
	ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	const ResourceManager& operator=(const ResourceManager&) = delete;

	template<typename ... Args>
	void load(const ID& id, Args&& ... args);

	sf::Music& get(const ID& id);

private:
	std::unordered_map<ID, std::unique_ptr<sf::Music>> _map;
};

template<typename ID>
template<typename ...Args>
inline void ResourceManager<sf::Music, ID>::load(const ID& id, Args && ...args)
{
	auto resource = std::make_unique<sf::Music>();
	if (!resource->openFromFile(std::forward<Args>(args) ...)) {
		throw std::runtime_error("Impossible to load file");
	}
	_map.emplace({ id, std::move(resource) });
}

template <typename ID>
inline sf::Music& ResourceManager<sf::Music, ID>::get(const ID& id)
{
	return *_map.at(id);
}