'use strict';

module.exports = function (grunt) {

    // Load tasks from grunt-* dependencies in package.json
    require('load-grunt-tasks')(grunt);

    // Time how long tasks take
    require('time-grunt')(grunt);

    // Project configuration
    grunt.initConfig({
        copy: {
            main: {
                files: [
                    { expand: true, flatten: true, src: ['build/*.wasm'], dest: 'dist/', filter: 'isFile' },
                ]
            }
        },
        connect: {
            options: {
                port: 9001,
                livereload: 35729,
                hostname: 'localhost'
            },
            livereload: {
                options: {
                    open: true
                }
            }
        },
        watch: {
            livereload: {
                files: [
                    'index.html',
                    'dist/*.js'
                ],
                options: {
                    livereload: '<%= connect.options.livereload %>'
                }
            },
        }
    });
    grunt.registerTask('serve', [
        'connect',
        'watch'
    ]);
};
