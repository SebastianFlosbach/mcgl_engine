#pragma once

#include "Block.h"
#include "KeyEvent.h"
#include "KeyEventCallback.h"
#include "KeyEventType.h"
#include "MouseEvent.h"
#include "MouseEventCallback.h"
#include "MouseEventType.h"


namespace conversion {


void construct( JNIEnv* env ) {
	Block::construct( env );
	KeyEvent::construct( env );
	KeyEventCallback::construct( env );
	KeyEventType::construct( env );
	MouseEvent::construct( env );
	MouseEventCallback::construct( env );
	MouseEventType::construct( env );
}

void destruct( JNIEnv* env ) {
	Block::destruct( env );
	KeyEvent::destruct( env );
	KeyEventCallback::destruct( env );
	KeyEventType::destruct( env );
	MouseEvent::destruct( env );
	MouseEventCallback::destruct( env );
	MouseEventType::destruct( env );
}


}