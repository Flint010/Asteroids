set(GAME_SOURCES
			Game.cpp
			Entity.cpp
			World/world.cpp
			Player.cpp
			Collision.cpp
			Action/Action.cpp
)
set(GAME_HEADERS 
			Game.h
			Entity.h
			World/world.h
			Player.h
			Collision.h
			resource.h
			Action/Action.h
			Action/ActionMap.h
			Action/ActionTarget.h
)

set(SHOOT_SOURCES
			Shoot/Shoot.cpp
			Shoot/ShootPlayer.cpp
			Shoot/ShootSaucer.cpp
)
set(SHOOT_HEADERS
			Shoot/Shoot.h
			Shoot/ShootPlayer.h
			Shoot/ShootSaucer.h
)

set(ENEMY_SOURCES
			Enemy/Enemy.cpp
			Enemy/Meteor/BigMeteor.cpp
			Enemy/Meteor/MediumMeteor.cpp
			Enemy/Meteor/Meteor.cpp
			Enemy/Meteor/SmallMeteor.cpp
			Enemy/Saucer/BigSaucer.cpp
			Enemy/Saucer/Saucer.cpp
			Enemy/Saucer/SmallSaucer.cpp
)
set(ENEMY_HEADERS
			Enemy/Enemy.h
			Enemy/Meteor/BigMeteor.h
			Enemy/Meteor/MediumMeteor.h
			Enemy/Meteor/Meteor.h
			Enemy/Meteor/SmallMeteor.h
			Enemy/Saucer/BigSaucer.h
			Enemy/Saucer/Saucer.h
			Enemy/Saucer/SmallSaucer.h
)

set(CONFIG_SOURCES
			Configuration/Configuration.cpp
			Configuration/Configuration.h
			Configuration/ResourceManager.h
)

add_executable(asteroids 
				main.cpp
				${GAME_SOURCES}
				${GAME_HEADERS}
				${SHOOT_SOURCES}
				${SHOOT_HEADERS}
				${ENEMY_SOURCES}
				${ENEMY_HEADERS}
				${CONFIG_SOURCES}
)

file(COPY ${CMAKE_SOURCE_DIR}/Asteroids/media DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)

find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

target_link_libraries(asteroids PRIVATE sfml-system sfml-graphics sfml-window sfml-audio)
