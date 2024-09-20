#include "hlsl++/quaternion.h"
#include "hlsl++/dependent.h"

#include "unit_tests.h"

void RunUnitTestsQuaternion()
{
	using namespace hlslpp_unit;

	//------------
	// Quaternions
	//------------

	float f1 = (float)(rand() % 1000) / 100.0f;
	float f2 = (float)(rand() % 1000) / 100.0f;
	float f3 = (float)(rand() % 1000) / 100.0f;

	float3 test_vector = normalize(float3(2, 9, 1));

	float3 x_axis = float3(1.0f, 0.0f, 0.0f);
	float3 y_axis = float3(0.0f, 1.0f, 0.0f);
	float3 z_axis = float3(0.0f, 0.0f, 1.0f);

	float r_x = f1;
	float r_y = f2;
	float r_z = f3;

	// Rotation X tests
	{
		quaternion q_x_axis      = quaternion::rotation_axis(x_axis, r_x);
		quaternion q_x_rot       = quaternion::rotation_x(r_x);
		quaternion q_x_euler_zxy = quaternion::rotation_euler_zxy(float3(r_x, 0.0f, 0.0f));

		float3x3 m_x_axis        = float3x3::rotation_axis(x_axis, r_x);
		float3x3 m_x_rot         = float3x3::rotation_x(r_x);
		float3x3 mq_x_axis       = float3x3(q_x_axis);
		float3x3 mq_x_rot        = float3x3(q_x_rot);
		float3x3 mq_x_euler_zxy  = float3x3(q_x_euler_zxy);

		float3 v_q_x_axis         = mul(test_vector, q_x_axis); hlslpp_unit_unused(v_q_x_axis);
		float3 v_q_x_axis_inv     = mul(q_x_axis, test_vector); hlslpp_unit_unused(v_q_x_axis_inv);
		float3 v_q_x_axis_mul     = mul(q_x_axis, mul(quaternion(test_vector), conjugate(q_x_axis))).xyz; hlslpp_unit_unused(v_q_x_axis_mul);
		float3 v_q_x_rot          = mul(test_vector, q_x_rot); hlslpp_unit_unused(v_q_x_rot);
		float3 v_q_x_euler_zxy    = mul(test_vector, q_x_euler_zxy); hlslpp_unit_unused(v_q_x_euler_zxy);

		float3 v_m_x_axis         = mul(test_vector, m_x_axis); hlslpp_unit_unused(v_m_x_axis);
		float3 v_m_x_rot          = mul(test_vector, m_x_rot); hlslpp_unit_unused(v_m_x_rot);
		float3 v_mq_x_axis        = mul(test_vector, mq_x_axis); hlslpp_unit_unused(v_mq_x_axis);
		float3 v_mq_x_rot         = mul(test_vector, mq_x_rot); hlslpp_unit_unused(v_mq_x_rot);
		float3 v_mq_x_euler_zxy   = mul(test_vector, mq_x_euler_zxy); hlslpp_unit_unused(v_mq_x_euler_zxy);
	}

	// Rotation Y tests
	{
		quaternion q_y_axis      = quaternion::rotation_axis(y_axis, r_y);
		quaternion q_y_rot       = quaternion::rotation_y(r_y);
		quaternion q_y_euler_zxy = quaternion::rotation_euler_zxy(float3(0.0f, r_y, 0.0f));

		float3x3 m_y_axis        = float3x3::rotation_axis(y_axis, r_y);
		float3x3 m_y_rot         = float3x3::rotation_y(r_y);
		float3x3 mq_y_axis       = float3x3(q_y_axis);
		float3x3 mq_y_rot        = float3x3(q_y_rot);
		float3x3 mq_y_euler_zxy  = float3x3(q_y_euler_zxy);

		float3 v_q_y_axis         = mul(test_vector, q_y_axis); hlslpp_unit_unused(v_q_y_axis);
		float3 v_q_y_axis_inv     = mul(q_y_axis, test_vector); hlslpp_unit_unused(v_q_y_axis_inv);
		float3 v_q_y_axis_mul     = mul(q_y_axis, mul(quaternion(test_vector), conjugate(q_y_axis))).xyz; hlslpp_unit_unused(v_q_y_axis_mul);
		float3 v_q_y_rot          = mul(test_vector, q_y_rot); hlslpp_unit_unused(v_q_y_rot);
		float3 v_q_y_euler_zxy    = mul(test_vector, q_y_euler_zxy); hlslpp_unit_unused(v_q_y_euler_zxy);

		float3 v_m_y_axis         = mul(test_vector, m_y_axis); hlslpp_unit_unused(v_m_y_axis);
		float3 v_m_y_rot          = mul(test_vector, m_y_rot); hlslpp_unit_unused(v_m_y_rot);
		float3 v_mq_y_axis        = mul(test_vector, mq_y_axis); hlslpp_unit_unused(v_mq_y_axis);
		float3 v_mq_y_rot         = mul(test_vector, mq_y_rot); hlslpp_unit_unused(v_mq_y_rot);
		float3 v_mq_y_euler_zxy   = mul(test_vector, mq_y_euler_zxy); hlslpp_unit_unused(v_mq_y_euler_zxy);
	}

	// Rotation Z tests
	{
		quaternion q_z_axis      = quaternion::rotation_axis(z_axis, r_z);
		quaternion q_z_rot       = quaternion::rotation_z(r_z);
		quaternion q_z_euler_zxy = quaternion::rotation_euler_zxy(float3(0.0f, 0.0f, r_z));

		float3x3 m_z_axis        = float3x3::rotation_axis(z_axis, r_z);
		float3x3 m_z_rot         = float3x3::rotation_z(r_z);
		float3x3 mq_z_axis       = float3x3(q_z_axis);
		float3x3 mq_z_rot        = float3x3(q_z_rot);
		float3x3 mq_z_euler_zxy  = float3x3(q_z_euler_zxy);

		float3 v_q_z_axis         = mul(test_vector, q_z_axis); hlslpp_unit_unused(v_q_z_axis);
		float3 v_q_z_axis_inv     = mul(q_z_axis, test_vector); hlslpp_unit_unused(v_q_z_axis_inv);
		float3 v_q_z_axis_mul     = mul(q_z_axis, mul(quaternion(test_vector), conjugate(q_z_axis))).xyz; hlslpp_unit_unused(v_q_z_axis_mul);
		float3 v_q_z_rot          = mul(test_vector, q_z_rot); hlslpp_unit_unused(v_q_z_rot);
		float3 v_q_z_euler_zxy    = mul(test_vector, q_z_euler_zxy); hlslpp_unit_unused(v_q_z_euler_zxy);

		float3 v_m_z_axis         = mul(test_vector, m_z_axis); hlslpp_unit_unused(v_m_z_axis);
		float3 v_m_z_rot          = mul(test_vector, m_z_rot); hlslpp_unit_unused(v_m_z_rot);
		float3 v_mq_z_axis        = mul(test_vector, mq_z_axis); hlslpp_unit_unused(v_mq_z_axis);
		float3 v_mq_z_rot         = mul(test_vector, mq_z_rot); hlslpp_unit_unused(v_mq_z_rot);
		float3 v_mq_z_euler_zxy   = mul(test_vector, mq_z_euler_zxy); hlslpp_unit_unused(v_mq_z_euler_zxy);
	}

	// This test demonstrates that matrix and quaternion concatenation
	// are reversed with respect to each other, i.e. a rotation A 
	// followed by a rotation B is expressed as
	// 
	// M_AB = M_A * M_B -> mul(v, M_AB)
	// Q_AB = Q_B * Q_A -> mul(v, Q_AB)
	// 
	// This is because quaternion rotation is defined as:
	// 
	// rotate(v, q_A) = q_A * v * q_A'
	// 
	// To apply the next rotation, we'd end up with
	// 
	// q_B * q_A * v * q_A' * q_B'
	// 
	// It is similar to how in matrix premultiplication it also looks "reversed",
	// i.e. when doing mul(M_AB, v) the correct transform is M_AB = M_B * M_A
	//
	
	{
		float angle = 3.14159f / 4.0f;

		quaternion q_x_axis      = quaternion::rotation_axis(x_axis, angle);
		quaternion q_z_axis      = quaternion::rotation_axis(z_axis, angle);
		quaternion q_xz_combined = mul(q_x_axis, q_z_axis);
		float3 v_q_xz_combined   = mul(test_vector, q_xz_combined); hlslpp_unit_unused(v_q_xz_combined);

		float3x3 m_x_axis = float3x3::rotation_axis(x_axis, angle);
		float3x3 m_z_axis = float3x3::rotation_axis(z_axis, angle);
		float3x3 m_xz_combined = mul(m_z_axis, m_x_axis);
		float3 v_m_xz_combined = mul(test_vector, m_xz_combined); hlslpp_unit_unused(v_m_xz_combined);
	}

	// Quaternion tests
	{
		quaternion q1 = quaternion::identity();
		quaternion q2 = quaternion(0.0f, 1.0f, 1.0f, 1.0f);

		quaternion slerp1 = slerp(q1, q2, 0.0f); hlslpp_unit_unused(slerp1);
		quaternion slerp2 = slerp(q1, q2, 1.0f); hlslpp_unit_unused(slerp2);
		quaternion slerp3 = slerp(q1, q2, 0.5f); hlslpp_unit_unused(slerp3);

		float3x3 mat3x3FromQuat = float3x3(q1); hlslpp_unit_unused(mat3x3FromQuat);
		float4x4 mat4x4FromQuat = float4x4(q1); hlslpp_unit_unused(mat4x4FromQuat);
	}
}