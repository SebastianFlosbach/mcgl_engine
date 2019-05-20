#pragma once

namespace conversion {


static constexpr const char* JAVA_CLASS_BLOCK =							"Block";
static constexpr const char* JAVA_BLOCK_FIELD_ID =						"id_";
static constexpr const char* JAVA_BLOCK_SIGNATURE_ID =					"I";
static constexpr const char* JAVA_BLOCK_FIELD_IS_TRANSPARENT =			"isTransparent_";
static constexpr const char* JAVA_BLOCK_SIGNATURE_IS_TRANSPARENT =		"Z";
static constexpr const char* JAVA_BLOCK_FIELD_LEFT_TEXTURE_ID =			"leftTextureId_";
static constexpr const char* JAVA_BLOCK_SIGNATURE_LEFT_TEXTURE_ID =		"I";
static constexpr const char* JAVA_BLOCK_FIELD_RIGHT_TEXTURE_ID =		"rightTextureId_";
static constexpr const char* JAVA_BLOCK_SIGNATURE_RIGHT_TEXTURE_ID =	"I";
static constexpr const char* JAVA_BLOCK_FIELD_TOP_TEXTURE_ID =			"topTextureId_";
static constexpr const char* JAVA_BLOCK_SIGNATURE_TOP_TEXTURE_ID =		"I";
static constexpr const char* JAVA_BLOCK_FIELD_BOTTOM_TEXTURE_ID =		"bottomTextureId_";
static constexpr const char* JAVA_BLOCK_SIGNATURE_BOTTOM_TEXTURE_ID =	"I";
static constexpr const char* JAVA_BLOCK_FIELD_FRONT_TEXTURE_ID =		"frontTextureId_";
static constexpr const char* JAVA_BLOCK_SIGNATURE_FRONT_TEXTURE_ID =	"I";
static constexpr const char* JAVA_BLOCK_FIELD_BACK_TEXTURE_ID =			"backTextureId_";
static constexpr const char* JAVA_BLOCK_SIGNATURE_BACK_TEXTURE_ID =		"I";

static constexpr const char* JAVA_METHOD_CONSTRUCTOR = "<init>";

static constexpr const char* JAVA_CLASS_KEY_EVENT_CALLBACK =				"IKeyEventCallback";
static constexpr const char* JAVA_KEY_EVENT_CALLBACK_METHOD_INVOKE =		"invoke";
static constexpr const char* JAVA_KEY_EVENT_CALLBACK_SIGNATURE_INVOKE =		"(LKeyEvent;)V";
static constexpr const char* JAVA_CLASS_KEY_EVENT =							"KeyEvent";
static constexpr const char* JAVA_KEY_EVENT_SIGNATURE_CONSTRUCTOR =			"(LEKeyEventType;IF)";
static constexpr const char* JAVA_ENUM_KEY_EVENT_TYPE =						"EKeyEventType";
static constexpr const char* JAVA_KEY_EVENT_TYPE_STATIC_FIELD_PRESSED =		"Pressed";
static constexpr const char* JAVA_KEY_EVENT_TYPE_STATIC_FIELD_DOWN =		"Down";
static constexpr const char* JAVA_KEY_EVENT_TYPE_STATIC_FIELD_RELEASED =	"Released";

static constexpr const char* JAVA_CLASS_MOUSE_EVENT =						"MouseEvent";

static constexpr const char* JAVA_CLASS_CHUNK =							"Chunk";
static constexpr const char* JAVA_CLASS_WORLD_COORDINATES =				"WorldCoordinates";
static constexpr const char* JAVA_WORLD_COORDINATES_SIGNATURE_CONSTRUCTOR = "(FFF)V";


}