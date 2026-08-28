// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <QObject>
#include <gtest/gtest.h>
#include "probe_context.hpp"

using quite::probe::ProbeContext;

TEST(QtProbeContext, CanBeConstructedAndDestructed)
{
    // Should not crash or throw
    ProbeContext ctx{"localhost:12345"};
}

TEST(QtProbeContext, InstallsAndRestoresQtHooks)
{
    // Check if hooks are restored on destruction
    {
        ProbeContext ctx{"localhost:12345"};
        EXPECT_NE(qtHookData[QHooks::AddQObject], 0);
        EXPECT_NE(qtHookData[QHooks::RemoveQObject], 0);
        EXPECT_NE(qtHookData[QHooks::Startup], 0);
    }
    EXPECT_EQ(qtHookData[QHooks::AddQObject], 0);
    EXPECT_EQ(qtHookData[QHooks::RemoveQObject], 0);
    EXPECT_EQ(qtHookData[QHooks::Startup], 0);
}
