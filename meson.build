project('defendguin_neo', 'cpp', subproject_dir: '')

#subproject('cog2d')

cog2d_dep = dependency('cog2d')

dgn_sources = files(
	'src/constants.hpp',
	'src/gameactorfactory.hpp',
	'src/bullet.cpp',
	'src/bullet.hpp',
	'src/bulletrocket.cpp',
	'src/bulletrocket.hpp',
	'src/bulletrocket2.cpp',
	'src/bulletrocket2.hpp',
	'src/camera.cpp',
	'src/camera.hpp',
	'src/cog2dintro.cpp',
	'src/cog2dintro.hpp',
	'src/gamescene.cpp',
	'src/gamescene.hpp',
	'src/main.cpp',
	'src/player.cpp',
	'src/player.hpp',
	'src/weapon.cpp',
	'src/weapon.hpp',
	'src/weaponbullet.cpp',
	'src/weaponbullet.hpp',
	'src/weaponpeashooter.cpp',
	'src/weaponpeashooter.hpp',
	'src/weaponrocket.cpp',
	'src/weaponrocket.hpp',
	'src/enemy.cpp',
	'src/enemy.hpp',
	'src/enemybullet.cpp',
	'src/enemybullet.hpp',
	'src/enemyfighter.cpp',
	'src/enemyfighter.hpp',
	'src/gameactorfactory.cpp',
)
executable('defendguin_neo', dgn_sources,
		   win_subsystem: 'windows',
		   dependencies: [cog2d_dep])
