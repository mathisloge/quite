# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

from __future__ import annotations

import quite


def test_version():
    assert quite.__version__


def test_git_version():
    assert quite.__version_git_ref__
