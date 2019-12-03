# Define Actor using function library() and declare dependency of Actor_dep
UnionFind = library('UnionFind',
    sources:['UF.hpp', 'UF.cpp'],
    dependencies : [ActorMovie_dep, ActorGraph_dep])

inc = include_directories('.')

UnionFind_dep = declare_dependency(include_directories: inc,
  link_with: UnionFind)

