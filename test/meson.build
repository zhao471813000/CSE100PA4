#Define dependencies of test files 
test_Actor_exe = executable ('test_Actor.cpp.executable',
    sources: ['test_Actor.cpp'],
    dependencies : [ActorMovie_dep, gtest_dep])
test('my Actor test', test_Actor_exe)

test_ActorGraph_exe = executable ('test_ActorGraph.cpp.executable',
    sources: ['test_ActorGraph.cpp'],
    dependencies : [ActorGraph_dep, ActorMovie_dep, gtest_dep])
test('my ActorGraph test', test_ActorGraph_exe)

test_Movie_exe = executable ('test_Movie.cpp.executable',
    sources: ['test_Movie.cpp'],
    dependencies : [ActorMovie_dep, gtest_dep])
test('my Movie test', test_Movie_exe)

