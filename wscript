#! /usr/bin/env python
# encoding: utf-8

import os
import shutil
import waflib.extras.wurf_options

APPNAME = 'fifi-calc'
VERSION = '0.0.0'


def options(opt):

    opt.load('wurf_common_tools')


def resolve(ctx):

    import waflib.extras.wurf_dependency_resolve as resolve

    ctx.load('wurf_common_tools')

    ctx.add_dependency(resolve.ResolveVersion(
        name='waf-tools',
        git_repository='github.com/steinwurf/waf-tools.git',
        major=3))

    ctx.add_dependency(resolve.ResolveVersion(
        name='fifi',
        git_repository='github.com/steinwurf/fifi.git',
        major=24))


def configure(conf):

    conf.load("wurf_common_tools")


def build(bld):

    bld.load("wurf_common_tools")

    bld.env.append_unique(
        'DEFINES_STEINWURF_VERSION',
        'STEINWURF_FIFI_CALC_VERSION="{}"'.format(VERSION))

    bld.recurse('src/fifi_calc')


def fix_bundle_dependencies(ctx):
    '''Fixes the version of dependencies stored in "bundle_dependencies"'''
    print('Removing all files in "bundle_dependencies/*/master/**"')

    nodes = ctx.path.ant_glob('bundle_dependencies/*/master', dir=True)

    def onerror(func, path, exc_info):
        """
        Error handler for shutil.rmtree to remove read-only files.
        """
        import stat
        if not os.access(path, os.W_OK):
            # Is the error an access error ?
            os.chmod(path, stat.S_IWUSR)
            func(path)
        else:
            raise

    for node in nodes:
        path = node.abspath()
        shutil.rmtree(path, onerror=onerror)
        os.mkdir(path)

    # Create a fake local repo in "bundle_dependencies" to prevent the
    # execution of git commands in the project root
    ctx.cmd_and_log('git init\n', cwd='bundle_dependencies')

    print('WARNING: The dependencies will not be updated after this! If you '
           'want to update, then delete the "bundle_dependencies" folder '
           '(or the corresponding subfolders).')
