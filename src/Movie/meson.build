# Define Movie using function library() and declare dependency of Movie_dep
Movie = library('Movie',
    sources:['Movie.hpp', 'Movie.cpp'])

inc = include_directories('.')

Movie_dep = declare_dependency(include_directories: inc,
  link_with: Movie)