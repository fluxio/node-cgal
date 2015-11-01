{
    'targets': [{

        'target_name': 'cgal',

        'sources': [
            'src/cgal.cc',
            'src/AffTransformation2.cc',
            'src/Arrangement2.cc',
            'src/Arrangement2Face.cc',
            'src/Arrangement2Halfedge.cc',
            'src/Arrangement2Vertex.cc',
            'src/BBox2.cc',
            'src/Curve2.cc',
            'src/D2.cc',
            'src/Direction2.cc',
            'src/Line2.cc',
            'src/NefPolyhedron2.cc',
            'src/Point2.cc',
            'src/Polygon2.cc',
            'src/PolygonSet2.cc',
            'src/PolygonWithHoles2.cc',
            'src/Ray2.cc',
            'src/Segment2.cc',
            'src/Vector2.cc'
         ],

        'include_dirs': [ '<!@(echo $CGAL_GYP_INCLUDES)' ],

        'conditions': [

            ['OS=="mac"', {
                'libraries': [ 'libCGAL.a', 'libgmp.a', 'libmpfr.a', 'libboost_thread-mt.a' ],
                'xcode_settings': {
                    'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                    'GCC_ENABLE_CPP_RTTI': 'YES',
                    'OTHER_CPLUSPLUSFLAGS': [
                        '-Wno-unneeded-internal-declaration',
                        '-mmacosx-version-min=10.11',
                        '-stdlib=libc++',
                        '<!@(echo $CGAL_GYP_CXXFLAGS)'
                     ],
                    'OTHER_LDFLAGS': [ '<!@(echo $CGAL_GYP_LDFLAGS)' ]
                }
            }],

            ['OS=="linux"', {
                'cflags_cc!': [ '-fno-exceptions', '-fno-rtti' ],
                'cflags_cc': [
                    '-frounding-math',
                    '<!@(echo $CGAL_GYP_CXXFLAGS)'
                ],
                'libraries': [ '-lCGAL', '-lgmp', '-lmpfr', '-lboost_thread' ],
                'ldflags': [ '<!@(echo $CGAL_GYP_LDFLAGS)', '-Bstatic ' ]
            }]

        ]

    }]
}
