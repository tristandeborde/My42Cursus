#ifndef RULE_SPEC_HPP
#define	RULE_SPEC_HPP

#include <string>

#include "utils/preprocessor.hpp"

// Rule Type
enum class eRuleType{
	Bool,
	Integer,
	Custom,
	List
};

// Rules name List Definition
#define	ALL_RULES_NAMES \
	P1001, \
	P1002, \
	P1003, \
	P1004, \
	P1005, \
	P1006, \
	P1007, \
	P1010, \
	P1011, \
	P1012, \
	P1021, \
	P1022, \
	P1023, \
	P1024, \
	M2001

enum class eRuleName{
	ALL_RULES_NAMES,
	COUNT
};

const std::string	RuleNameToString(const eRuleName &);

// Custom types Definition
enum class C_Bot{
	Noob
};

enum class C_Freq{
	VeryRare,
	Rare,
	Normal,
	Frequent,
	VeryFrequent,
	OneByOne
};

enum class C_Object{
	Fruit,
	Bomb,
	DestructibleWall
};

enum class C_End{
	Collision,
	NoHP,
	ScoreLimit
};

#define		NAMERULE_TYPE_P1001()		 INT
#define		NAMERULE_NAME_P1001()		 "Window Width"
#define		NAMERULE_MIN_P1001()		 15
#define		NAMERULE_MAX_P1001()		 40
#define		NAMERULE_VAL_P1001()		 20

#define		NAMERULE_TYPE_P1002()		 INT
#define		NAMERULE_NAME_P1002()		 "Window Height"
#define		NAMERULE_MIN_P1002()		 15
#define		NAMERULE_MAX_P1002()		 40
#define		NAMERULE_VAL_P1002()		 20

#define		NAMERULE_TYPE_P1003()		 INT
#define		NAMERULE_NAME_P1003()		 "Nb players"
#define		NAMERULE_MIN_P1003()		 1
#define		NAMERULE_MAX_P1003()		 8
#define		NAMERULE_VAL_P1003()		 4

#define		NAMERULE_TYPE_P1004()		 CUSTOM
#define		NAMERULE_NAME_P1004()		 "Bot Difficulty"
#define		NAMERULE_CUSTOM_TYPE_P1004() C_Bot
#define		NAMERULE_CUSTOM_DEF_P1004()	 C_Bot::Noob

#define		NAMERULE_TYPE_P1005()		 BOOL
#define		NAMERULE_NAME_P1005()		 "Surround Walls"
#define		NAMERULE_GET_BOOL_P1005()	 true

#define		NAMERULE_TYPE_P1006()		 BOOL
#define		NAMERULE_NAME_P1006()		 "Destructible Walls"
#define		NAMERULE_GET_BOOL_P1006()	 false

#define		NAMERULE_TYPE_P1007()		 LIST
#define		NAMERULE_NAME_P1007()		 "Game End"
#define		NAMERULE_LIST_TYPE_P1007()	 C_End
#define		NAMERULE_LIST_DEF_P1007()	 ListRule<C_End>::ContainerType {C_End::NoHP, C_End::Collision}

#define		NAMERULE_TYPE_P1010()		 BOOL
#define		NAMERULE_NAME_P1010()		 "Has Body"
#define		NAMERULE_GET_BOOL_P1010()	 true

#define		NAMERULE_TYPE_P1011()		 BOOL
#define		NAMERULE_NAME_P1011()		 "Speed Increase"
#define		NAMERULE_GET_BOOL_P1011()	 true

#define		NAMERULE_TYPE_P1012()		 BOOL
#define		NAMERULE_NAME_P1012()		 "Drop Bomb"
#define		NAMERULE_GET_BOOL_P1012()	 false

#define		NAMERULE_TYPE_P1021()		 LIST
#define		NAMERULE_NAME_P1021()		 "Spawn Obj Init"
#define		NAMERULE_LIST_TYPE_P1021()	 C_Object
#define		NAMERULE_LIST_DEF_P1021()	 ListRule<C_Object>::ContainerType()

#define		NAMERULE_TYPE_P1022()		 LIST
#define		NAMERULE_NAME_P1022()		 "Spawn Obj Game"
#define		NAMERULE_LIST_TYPE_P1022()	 C_Object
#define		NAMERULE_LIST_DEF_P1022()	 ListRule<C_Object>::ContainerType {C_Object::Fruit}

#define		NAMERULE_TYPE_P1023()		 CUSTOM
#define		NAMERULE_NAME_P1023()		 "Frequency Obj Init"
#define		NAMERULE_CUSTOM_TYPE_P1023() C_Freq
#define		NAMERULE_CUSTOM_DEF_P1023()	 C_Freq::Normal

#define		NAMERULE_TYPE_P1024()		 CUSTOM
#define		NAMERULE_NAME_P1024()		 "Frequency Obj Game"
#define		NAMERULE_CUSTOM_TYPE_P1024() C_Freq
#define		NAMERULE_CUSTOM_DEF_P1024()	 C_Freq::OneByOne


#define		NAMERULE_TYPE_M2001()	  BOOL
#define		NAMERULE_NAME_M2001()	  "Autorun"
#define		NAMERULE_GET_BOOL_M2001() true


// Helper Macros
#define		NAMERULE_TYPE(namerule)			   NAMERULE_TYPE_ ## namerule()
#define		NAMERULE_NAME(namerule)			   NAMERULE_NAME_ ## namerule()
#define		NAMERULE_GET_BOOL(namerule)		   NAMERULE_GET_BOOL_ ## namerule()
#define		NAMERULE_GET_INT_MIN(namerule)	   NAMERULE_MIN_ ## namerule()
#define		NAMERULE_GET_INT_MAX(namerule)	   NAMERULE_MAX_ ## namerule()
#define		NAMERULE_GET_INT_VAL(namerule)	   NAMERULE_VAL_ ## namerule()
#define		NAMERULE_GET_CUSTOM_TYPE(namerule) NAMERULE_CUSTOM_TYPE_ ## namerule()
#define		NAMERULE_GET_CUSTOM_DEF(namerule)  NAMERULE_CUSTOM_DEF_ ## namerule()
#define		NAMERULE_GET_LIST_TYPE(namerule)   NAMERULE_LIST_TYPE_ ## namerule()
#define		NAMERULE_GET_LIST_DEF(namerule)	   NAMERULE_LIST_DEF_ ## namerule()

#define		FOR_EACH_RULE_(what, rules)		   FOR_EACH(what, rules)
#define		FOR_EACH_RULE(what)				   FOR_EACH_RULE_(what, ALL_RULES_NAMES)

#endif	// ifndef RULE_SPEC_HPP
