#  Define pathfinder_exe and linkpredictor_exe to output executable file named 
#  pathfinder.cpp.executable and linkpredictor.cpp.executable
subdir('ActorMovie')
subdir('ActorGraph')
subdir('Edge')
subdir('UnionFind')
pathfinder_exe = executable('pathfinder.cpp.executable',
    sources: ['pathfinder.cpp'],
    dependencies : [ActorGraph_dep, ActorMovie_dep],
    install : true)

linkpredictor_exe = executable('linkpredictor.cpp.executable',
    sources: ['linkpredictor.cpp'],
    dependencies : [ActorGraph_dep, ActorMovie_dep],
    install : true)
    
movietraveler_exe = executable('movietraveler.cpp.executable',
    sources: ['movietraveler.cpp'],
    dependencies : [ActorGraph_dep, ActorMovie_dep, Edge_dep, UnionFind_dep],
    install : true)


