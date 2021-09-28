{
    'targets' : [
        {
            'target_name' : 'osu_performance',
            'defines' : [
                "CURL_STATICLIB"
            ],
            'include_dirs' : [
                "<!(node -e \"require('nan')\")",
                "./src/osu-performance/include",
                "./src/osu-performance/dependencies/curl/include",
                "./src/osu-performance/dependencies/json/include",
                "./src/osu-performance/dependencies/MySQL/include",
                "./src/osu-performance/dependencies/StrFormat",
                "./src/osu-performance/dependencies/tinylogger",
                "./src/osu-performance/dependencies/args",
            ],
            'conditions' : [
                ['OS=="win"', {
                    'libraries': [
                        "<(module_root_dir)/src/osu-performance/dependencies/curl/lib/libcurl.lib",
                        "<(module_root_dir)/src/osu-performance/dependencies/MySQL/lib/libmariadb.lib"
                    ],
                }],
                ['OS=="mac"', {
                    'libraries': [
                        "/usr/local/opt/mysql-client/lib"
                    ],
                }],
            ],
            'cflags_cc': [
                '-std=c++11',
            ],
            'sources' : [
                "src/init.cc",
                "<!@(node -p \"require('./getSourceFiles.js').walk('./src/osu-performance/src').map((s)=>s.replace(/\\\\/g,'/')).join(' ')\")",
            ],
			'copies' : [
				{
					"destination": "<(module_root_dir)/build/Release/",
					"files": [
						"<(module_root_dir)/src/osu-performance/dependencies/curl/dll/64bit/libcurl.dll",
						"<(module_root_dir)/src/osu-performance/dependencies/MySQL/dll/64bit/libmariadb.dll"
					]
				}
			]
        }
    ]
}