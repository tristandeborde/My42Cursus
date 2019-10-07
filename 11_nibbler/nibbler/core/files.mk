
_SRC_FILES :=

### exceptions/
_SRC_FILES += \
			exceptions/Exception.class.cpp \
			exceptions/GraphicsLoaderException.class.cpp \
			exceptions/LoggerException.class.cpp \
			exceptions/MapBuilderException.class.cpp \
			exceptions/CoreException.class.cpp \
			exceptions/RuleSetException.class.cpp

### game/components/
_SRC_FILES += \
			game/components/ComponentMove.class.cpp \
			game/components/ComponentCollision.class.cpp \
			game/components/ComponentRender.class.cpp \
			game/components/ComponentPlayer.class.cpp \
			game/components/ComponentTimerEvent.class.cpp \
			game/components/ComponentOnDeathEvent.class.cpp \
			game/components/ComponentDamage.class.cpp \
			game/components/ComponentHasBody.class.cpp \
			game/components/ComponentLifePoint.class.cpp \
			game/components/ComponentScore.class.cpp \
			game/components/IComponent.class.cpp

### game/system/
_SRC_FILES += \
			game/system/SystemInput.cpp \
			game/system/SystemTimer.cpp \
			game/system/SystemRender.cpp \
			game/system/SystemPhysics.cpp \

### game/clocks/
_SRC_FILES += \
			game/clocks/FrameClock.class.cpp \
			game/clocks/GameClock.class.cpp

### game/
_SRC_FILES += \
			game/Party.class.cpp \
			game/Entity.class.cpp \
			game/EntityFactory.cpp \
			game/MapBuilder.cpp

### menu/
_SRC_FILES += \
			menu/Menu.class.cpp \
			menu/Button.class.cpp

### rules/
_SRC_FILES += \
			rules/RuleSet.class.cpp \
			rules/rule_factory.cpp \
			rules/rule_spec.cpp \
			rules/ARule.class.cpp \
			rules/atom_rules/BoolRule.class.cpp \
			rules/atom_rules/IntRule.class.cpp

### utils/
_SRC_FILES += \
			utils/Logger.cpp \
			utils/GraphicsLoader.cpp

### in src directly
_SRC_FILES += \
			Core.cpp \
			MainMonad.class.cpp \
			ArgParser.class.cpp \
			main.cpp

SRC_FILES = $(addprefix $(SRC_FOLDER), $(_SRC_FILES))
