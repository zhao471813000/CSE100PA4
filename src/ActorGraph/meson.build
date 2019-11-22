# Define ActorGraph using function library() and declare dependency of ActorGraph_dep
ActorGraph = library('ActorGraph',
    sources:['ActorGraph.hpp', 'ActorGraph.cpp'],
    dependencies : [ActorMovie_dep])

inc = include_directories('.')

ActorGraph_dep = declare_dependency(include_directories: inc,
  link_with: ActorGraph)