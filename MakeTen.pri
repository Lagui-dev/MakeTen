!isEmpty(MAKETEN_PRI_INCLUDED):error("MakeTen.pri already included")

MAKETEN_PRI_INCLUDED = 1

APP_VERSION = 0.1.00
DISPLAY_VERSION = 0.1.00-beta1
COPYRIGHT_YEAR = 2021

isEmpty(IDE_DISPLAY_NAME) : IDE_DISPLAY_NAME = MakeTen
IDE_APP_TARGET   = "$$IDE_DISPLAY_NAME"
IDE_SOURCE_TREE = $$PWD

isEmpty(IDE_BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    IDE_BUILD_TREE = $$clean_path($$OUT_PWD)
    IDE_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}

#IDE_APP_PATH = $$IDE_BUILD_TREE/bin

CONFIG += c++14

defineTest(minQtVersion) {
    maj = $$1
    min = $$2
    patch = $$3
    isEqual(QT_MAJOR_VERSION, $$maj) {
        isEqual(QT_MINOR_VERSION, $$min) {
            isEqual(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
            greaterThan(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
        }
        greaterThan(QT_MINOR_VERSION, $$min) {
            return(true)
        }
    }
    greaterThan(QT_MAJOR_VERSION, $$maj) {
        return(true)
    }
    return(false)
}
