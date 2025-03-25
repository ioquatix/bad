// Copyright, 2025, by Samuel Williams.
// Released under the MIT License.

#include "ruby.h"

typedef struct {
	VALUE value; // Instance variable: @value
} bad_object_t;

static void bad_mark(void *pointer) {
	bad_object_t *object = (bad_object_t *)pointer;
	rb_gc_mark(object->value);
}

static void bad_free(void *pointer) {
	xfree(pointer);
}

static size_t bad_memsize(const void *pointer) {
	return sizeof(bad_object_t);
}

static const rb_data_type_t bad_type = {
	"Bad::Object",
	{
		bad_mark,
		bad_free,
		bad_memsize,
	},
	0, 0, RUBY_TYPED_FREE_IMMEDIATELY | RUBY_TYPED_WB_PROTECTED
};

static VALUE bad_allocate(VALUE klass) {
	bad_object_t *object = ALLOC(bad_object_t);
	object->value = Qnil;

	return TypedData_Wrap_Struct(klass, &bad_type, object);
}

static VALUE bad_initialize(VALUE self, VALUE value) {
	bad_object_t *object;
	TypedData_Get_Struct(self, bad_object_t, &bad_type, object);

	// ❌ Bug: No write barrier
	object->value = value;

	return self;
}

static VALUE bad_get_value(VALUE self) {
	bad_object_t *object;
	TypedData_Get_Struct(self, bad_object_t, &bad_type, object);

	return object->value;
}

static VALUE bad_set_value(VALUE self, VALUE value) {
	bad_object_t *object;
	TypedData_Get_Struct(self, bad_object_t, &bad_type, object);

	// ❌ Bug: Still no write barrier
	object->value = value;

	return value;
}

void Init_bad(void) {
	VALUE mBad = rb_define_module("Bad");
	VALUE cObject = rb_define_class_under(mBad, "Object", rb_cObject);

	rb_define_alloc_func(cObject, bad_allocate);
	rb_define_method(cObject, "initialize", bad_initialize, 1);
	rb_define_method(cObject, "value", bad_get_value, 0);
	rb_define_method(cObject, "value=", bad_set_value, 1);
}
