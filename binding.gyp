{
    'targets' : [
        {
            'target_name' : 'osu_performance',
            'defines' : [
                "CURL_STATICLIB"
            ],
            'dependencies' : [
                'args',
                'curl',
                'json',
                'MySQL',
                'StrFormat',
                'tinylogger'
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
        },
        {
            'target_name' : 'args',
            'cflags_cc': [
                '-std=c++11',
            ],
            'sources' : [
                "<!@(node -p \"require('./getSourceFiles.js').walk('./src/osu-performance/dependencies/args').map((s)=>s.replace(/\\\\/g,'/')).join(' ')\")"
            ],
        },
        {
            'target_name' : 'curl',
            'cflags_cc': [
                '-std=c++11',
            ],
            'sources' : [
                "<!@(node -p \"require('./getSourceFiles.js').walk('./src/osu-performance/dependencies/curl/include').map((s)=>s.replace(/\\\\/g,'/')).join(' ')\")"
            ],
        },
        {
            'target_name' : 'json',
            'cflags_cc': [
                '-std=c++11',
            ],
            'sources' : [
                "<!@(node -p \"require('./getSourceFiles.js').walk('./src/osu-performance/dependencies/json/include').map((s)=>s.replace(/\\\\/g,'/')).join(' ')\")"
            ],
        },
        {
            'target_name' : 'MySQL',
            'cflags_cc': [
                '-std=c++11',
            ],
            'sources' : [
                "<!@(node -p \"require('./getSourceFiles.js').walk('./src/osu-performance/dependencies/MySQL/include').map((s)=>s.replace(/\\\\/g,'/')).join(' ')\")"
            ],
        },
        {
            'target_name' : 'StrFormat',
            'cflags_cc': [
                '-std=c++11',
            ],
            'sources' : [
                "<!@(node -p \"require('./getSourceFiles.js').walk('./src/osu-performance/dependencies/StrFormat').map((s)=>s.replace(/\\\\/g,'/')).join(' ')\")"
            ],
        },
        {
            'target_name' : 'tinylogger',
            'cflags_cc': [
                '-std=c++11',
            ],
            'sources' : [
                "<!@(node -p \"require('./getSourceFiles.js').walk('./src/osu-performance/dependencies/tinylogger').map((s)=>s.replace(/\\\\/g,'/')).join(' ')\")"
            ],
        },
    ]
}