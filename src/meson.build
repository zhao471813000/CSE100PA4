#  Define pathfinder_exe and linkpredictor_exe to output executable file named 
#  pathfinder.cpp.executable and linkpredictor.cpp.executable
subdir('Actor')
subdir('Movie')
subdir('ActorGraph')

pathfinder_exe = executable('pathfinder.cpp.executable',
    sources: ['pathfinder.cpp'],
    dependencies : [ActorGraph_dep, Actor_dep, Movie_dep],
    install : true)

linkpredictor_exe = executable('linkpredictor.cpp.executable',
    sources: ['linkpredictor.cpp'],
    dependencies : [ActorGraph_dep, Actor_dep, Movie_dep],
    install : true)


