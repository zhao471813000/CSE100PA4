# Define Actor using function library() and declare dependency of Actor_dep
Edge = library('Edge',
    sources:['Edge.hpp'],
    dependencies : [ActorMovie_dep, ActorGraph_dep])

inc = include_directories('.')

Edge_dep = declare_dependency(include_directories: inc,
  link_with: Edge)

