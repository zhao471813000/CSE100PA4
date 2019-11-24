# Define Actor using function library() and declare dependency of Actor_dep
ActorMovie = library('ActorMovie',
    sources:['Actor.hpp', 'Movie.hpp'])

inc = include_directories('.')

ActorMovie_dep = declare_dependency(include_directories: inc,
  link_with: ActorMovie)