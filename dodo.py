from doit import create_after

DOIT_CONFIG = {
    'default_tasks': ['build_and_run'],
}

def task_build_and_run():
    """Build and run the C++ project"""
    return {
        'actions': ['python3 deploy.py run'],
        'verbosity': 2,
    }

def task_run_tests():
    """Run the tests"""
    return {
        'actions': ['python3 deploy.py run_tests'],
        'verbosity': 2,
    }