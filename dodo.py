from doit import create_after

DOIT_CONFIG = {
    'default_tasks': ['build_and_run'],
}

def task_build_and_run():
    """Build and run the C++ project"""
    return {
        'actions': ['python3 deploy.py'],
        'verbosity': 2,
    }