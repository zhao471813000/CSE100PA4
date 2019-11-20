# Define Actor using function library() and declare dependency of Actor_dep
Actor = library('Actor',
    sources:['Actor.hpp', 'Actor.cpp'])

inc = include_directories('.')

Actor_dep = declare_dependency(include_directories: inc,
  link_with: Actor)