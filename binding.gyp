{
    'targets': [{

        'target_name': 'cgal',

        'sources': [
            'src/cgal.cc',
            'src/Arrangement2.cc',
            'src/BBox2.cc',
            'src/D2.cc',
            'src/Line2.cc',
            'src/NefPolyhedron2.cc',
            'src/Point2.cc',
            'src/Polygon2.cc',
            'src/PolygonSet2.cc',
            'src/PolygonWithHoles2.cc',
            'src/Segment2.cc'
         ],

        'include_dirs': [ '<!@(echo $CGAL_GYP_INCLUDES)' ],

        'conditions': [

            ['OS=="mac"', {
                'libraries': [ 'libCGAL.a', 'libgmp.a', 'libboost_thread-mt.a' ],
                'xcode_settings': {
                    'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                    'GCC_ENABLE_CPP_RTTI': 'YES',
                    'OTHER_CPLUSPLUSFLAGS': [
                        '-Wno-unneeded-internal-declaration',
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
                'libraries': [ '-lCGAL', '-lgmp', '-lboost_thread' ],
                'ldflags': [ '<!@(echo $CGAL_GYP_LDFLAGS)', '-Bstatic ' ]
            }]

        ]

    }]
}
