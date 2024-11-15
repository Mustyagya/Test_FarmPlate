// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Test_FarmPlate/Public/BuildFarmActorComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBuildFarmActorComponent() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
TEST_FARMPLATE_API UClass* Z_Construct_UClass_AFarmPlotActor_NoRegister();
TEST_FARMPLATE_API UClass* Z_Construct_UClass_UBuildFarmActorComponent();
TEST_FARMPLATE_API UClass* Z_Construct_UClass_UBuildFarmActorComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_Test_FarmPlate();
// End Cross Module References

// Begin Class UBuildFarmActorComponent
void UBuildFarmActorComponent::StaticRegisterNativesUBuildFarmActorComponent()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UBuildFarmActorComponent);
UClass* Z_Construct_UClass_UBuildFarmActorComponent_NoRegister()
{
	return UBuildFarmActorComponent::StaticClass();
}
struct Z_Construct_UClass_UBuildFarmActorComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "BuildFarmActorComponent.h" },
		{ "ModuleRelativePath", "Public/BuildFarmActorComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MyFarmPlotActor_MetaData[] = {
		{ "Category", "FarmPlot" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xd0\x9e\xd0\xb1\xd0\xbd\xd0\xbe\xd0\xb2\xd0\xbb\xd0\xb5\xd0\xbd\xd0\xb8\xd0\xb5 \xd1\x80\xd0\xb0\xd0\xb7\xd0\xbc\xd0\xb5\xd1\x80\xd0\xb0 \xd0\xba\xd0\xbe\xd0\xbb\xd0\xbb\xd0\xb8\xd0\xb7\xd0\xb8\xd0\xbe\xd0\xbd\xd0\xbd\xd0\xbe\xd0\xb3\xd0\xbe \xd0\xb1\xd0\xbe\xd0\xba\xd1\x81\xd0\xb0\n" },
#endif
		{ "ModuleRelativePath", "Public/BuildFarmActorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xd0\x9e\xd0\xb1\xd0\xbd\xd0\xbe\xd0\xb2\xd0\xbb\xd0\xb5\xd0\xbd\xd0\xb8\xd0\xb5 \xd1\x80\xd0\xb0\xd0\xb7\xd0\xbc\xd0\xb5\xd1\x80\xd0\xb0 \xd0\xba\xd0\xbe\xd0\xbb\xd0\xbb\xd0\xb8\xd0\xb7\xd0\xb8\xd0\xbe\xd0\xbd\xd0\xbd\xd0\xbe\xd0\xb3\xd0\xbe \xd0\xb1\xd0\xbe\xd0\xba\xd1\x81\xd0\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MyFarmPlotActorBPClass_MetaData[] = {
		{ "Category", "FarmPlot" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xd0\xa5\xd1\x80\xd0\xb0\xd0\xbd\xd0\xb8\xd1\x82 \xd1\x81\xd1\x81\xd1\x8b\xd0\xbb\xd0\xba\xd1\x83 \xd0\xbd\xd0\xb0 Blueprint \xd0\xba\xd0\xbb\xd0\xb0\xd1\x81\xd1\x81\n" },
#endif
		{ "ModuleRelativePath", "Public/BuildFarmActorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xd0\xa5\xd1\x80\xd0\xb0\xd0\xbd\xd0\xb8\xd1\x82 \xd1\x81\xd1\x81\xd1\x8b\xd0\xbb\xd0\xba\xd1\x83 \xd0\xbd\xd0\xb0 Blueprint \xd0\xba\xd0\xbb\xd0\xb0\xd1\x81\xd1\x81" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FClassPropertyParams NewProp_MyFarmPlotActor;
	static const UECodeGen_Private::FClassPropertyParams NewProp_MyFarmPlotActorBPClass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBuildFarmActorComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UBuildFarmActorComponent_Statics::NewProp_MyFarmPlotActor = { "MyFarmPlotActor", nullptr, (EPropertyFlags)0x0014000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBuildFarmActorComponent, MyFarmPlotActor), Z_Construct_UClass_UClass, Z_Construct_UClass_AFarmPlotActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MyFarmPlotActor_MetaData), NewProp_MyFarmPlotActor_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UBuildFarmActorComponent_Statics::NewProp_MyFarmPlotActorBPClass = { "MyFarmPlotActorBPClass", nullptr, (EPropertyFlags)0x0014000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBuildFarmActorComponent, MyFarmPlotActorBPClass), Z_Construct_UClass_UClass, Z_Construct_UClass_AFarmPlotActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MyFarmPlotActorBPClass_MetaData), NewProp_MyFarmPlotActorBPClass_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBuildFarmActorComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBuildFarmActorComponent_Statics::NewProp_MyFarmPlotActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBuildFarmActorComponent_Statics::NewProp_MyFarmPlotActorBPClass,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBuildFarmActorComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UBuildFarmActorComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_Test_FarmPlate,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBuildFarmActorComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBuildFarmActorComponent_Statics::ClassParams = {
	&UBuildFarmActorComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UBuildFarmActorComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UBuildFarmActorComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBuildFarmActorComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UBuildFarmActorComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBuildFarmActorComponent()
{
	if (!Z_Registration_Info_UClass_UBuildFarmActorComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBuildFarmActorComponent.OuterSingleton, Z_Construct_UClass_UBuildFarmActorComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBuildFarmActorComponent.OuterSingleton;
}
template<> TEST_FARMPLATE_API UClass* StaticClass<UBuildFarmActorComponent>()
{
	return UBuildFarmActorComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBuildFarmActorComponent);
UBuildFarmActorComponent::~UBuildFarmActorComponent() {}
// End Class UBuildFarmActorComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_UnrealProjects_CppTask_Test_FarmPlate_Test_FarmPlate_Source_Test_FarmPlate_Public_BuildFarmActorComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBuildFarmActorComponent, UBuildFarmActorComponent::StaticClass, TEXT("UBuildFarmActorComponent"), &Z_Registration_Info_UClass_UBuildFarmActorComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBuildFarmActorComponent), 3781946277U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_CppTask_Test_FarmPlate_Test_FarmPlate_Source_Test_FarmPlate_Public_BuildFarmActorComponent_h_1064042985(TEXT("/Script/Test_FarmPlate"),
	Z_CompiledInDeferFile_FID_UnrealProjects_CppTask_Test_FarmPlate_Test_FarmPlate_Source_Test_FarmPlate_Public_BuildFarmActorComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_CppTask_Test_FarmPlate_Test_FarmPlate_Source_Test_FarmPlate_Public_BuildFarmActorComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
