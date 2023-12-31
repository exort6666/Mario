cmake_minimum_required(VERSION 3.15) # Проверка версии CMake.
									 # Если версия установленой программы
									 # старее указаной, произайдёт аварийный выход.

set(PROJECT_NAME Mario)				 # имя проекта		 
project("${PROJECT_NAME}")


set(CMAKE_CXX_STANDARD 17)			 # устанавливаем 17 стандарт языка
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


add_definitions(-DSFML_STATIC)		 # дефайны

include_directories("ext/SFML/include/")	# добавляем директории
include_directories("inc/")
link_directories("ext/SFML/lib/")	

add_executable("${PROJECT_NAME}" main.cpp
								
								inc/Character.hpp
								src/Character.cpp
								
								inc/Object.hpp
								src/Object.cpp
								
								inc/Block.hpp
								src/Block.cpp
								
								inc/Mobs.hpp
								src/Mobs.cpp
								
								inc/Logger.hpp
								src/Logger.cpp
								
								inc/Heart.hpp
								src/Heart.cpp
								
								AnimatedPers/_Run.png
								AnimatedPers/_TurnAround.png
								AnimatedPers/Comparison2x.png
								AnimatedPers/_Attack.png
								AnimatedPers/_Jump.png
								
								AnimatedSkeleton/Attack.png
								AnimatedSkeleton/Walk.png
								AnimatedSkeleton/Death.png
								AnimatedSkeleton/Idle.png
								AnimatedSkeleton/TakeHit.png
								
								Background/background.png
								Font/font.TTF
								Heart/Full.png
)
											
target_link_libraries("${PROJECT_NAME}" sfml-graphics-s-d
						  sfml-window-s-d
						  sfml-system-s-d
						  opengl32
						  freetype
						  winmm
						  gdi32
						  sfml-audio-s-d
						  openal32
						  flac
						  vorbisenc
						  vorbisfile
						  vorbis
						  ogg)