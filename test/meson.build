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

# test_Linkpredictor_exe = executable ('test_linkpredictor.cpp.executable',
#     sources: ['test_linkpredictor.cpp'],
#     dependencies : [ActorGraph_dep, ActorMovie_dep, gtest_dep])
# test('my Linkpredictor test', test_Linkpredictor_exe)

test_UF_exe = executable ('test_UF.cpp.executable',
    sources: ['test_UF.cpp'],
    dependencies : [ActorGraph_dep, ActorMovie_dep, gtest_dep, UnionFind_dep])
test('my UF test', test_UF_exe)

test_Edge_exe = executable ('test_Edge.cpp.executable',
    sources: ['test_Edge.cpp'],
    dependencies : [ActorGraph_dep, ActorMovie_dep, gtest_dep, Edge_dep])
test('my Edge test', test_Edge_exe)

test_movietraveler_exe = executable ('test_movietraveler.cpp.executable',
    sources: ['test_movietraveler.cpp'],
    dependencies : [ActorGraph_dep, ActorMovie_dep, gtest_dep, Edge_dep, UnionFind_dep])
test('my movietraveler test', test_movietraveler_exe)
