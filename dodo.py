from doit import task


DOIT_CONFIG = {
    'default_tasks': ['run_project'],
}


def task_build():
    """Build the project"""
    return {
        'actions': ['python3 deploy.py build'],
        'verbosity': 2,
    }


def task_run_project():
    """Run the C++ project"""
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
