// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Test_FarmPlate/Public/FarmPlotActor.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFarmPlotActor() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UBoxComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
TEST_FARMPLATE_API UClass* Z_Construct_UClass_AFarmPlotActor();
TEST_FARMPLATE_API UClass* Z_Construct_UClass_AFarmPlotActor_NoRegister();
UPackage* Z_Construct_UPackage__Script_Test_FarmPlate();
// End Cross Module References

// Begin Class AFarmPlotActor Function InitializePlot
struct Z_Construct_UFunction_AFarmPlotActor_InitializePlot_Statics
{
	struct FarmPlotActor_eventInitializePlot_Parms
	{
		FVector PlotLocation;
		FVector PlotSIze;
		FVector InMeshOffset;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Plot" },
		{ "ModuleRelativePath", "Public/FarmPlotActor.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_PlotLocation;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PlotSIze;
	static const UECodeGen_Private::FStructPropertyParams NewProp_InMeshOffset;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AFarmPlotActor_InitializePlot_Statics::NewProp_PlotLocation = { "PlotLocation", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FarmPlotActor_eventInitializePlot_Parms, PlotLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AFarmPlotActor_InitializePlot_Statics::NewProp_PlotSIze = { "PlotSIze", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FarmPlotActor_eventInitializePlot_Parms, PlotSIze), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AFarmPlotActor_InitializePlot_Statics::NewProp_InMeshOffset = { "InMeshOffset", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FarmPlotActor_eventInitializePlot_Parms, InMeshOffset), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AFarmPlotActor_InitializePlot_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AFarmPlotActor_InitializePlot_Statics::NewProp_PlotLocation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AFarmPlotActor_InitializePlot_Statics::NewProp_PlotSIze,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AFarmPlotActor_InitializePlot_Statics::NewProp_InMeshOffset,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AFarmPlotActor_InitializePlot_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AFarmPlotActor_InitializePlot_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AFarmPlotActor, nullptr, "InitializePlot", nullptr, nullptr, Z_Construct_UFunction_AFarmPlotActor_InitializePlot_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AFarmPlotActor_InitializePlot_Statics::PropPointers), sizeof(Z_Construct_UFunction_AFarmPlotActor_InitializePlot_Statics::FarmPlotActor_eventInitializePlot_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AFarmPlotActor_InitializePlot_Statics::Function_MetaDataParams), Z_Construct_UFunction_AFarmPlotActor_InitializePlot_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AFarmPlotActor_InitializePlot_Statics::FarmPlotActor_eventInitializePlot_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AFarmPlotActor_InitializePlot()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AFarmPlotActor_InitializePlot_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AFarmPlotActor::execInitializePlot)
{
	P_GET_STRUCT(FVector,Z_Param_PlotLocation);
	P_GET_STRUCT(FVector,Z_Param_PlotSIze);
	P_GET_STRUCT(FVector,Z_Param_InMeshOffset);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->InitializePlot(Z_Param_PlotLocation,Z_Param_PlotSIze,Z_Param_InMeshOffset);
	P_NATIVE_END;
}
// End Class AFarmPlotActor Function InitializePlot

// Begin Class AFarmPlotActor
void AFarmPlotActor::StaticRegisterNativesAFarmPlotActor()
{
	UClass* Class = AFarmPlotActor::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "InitializePlot", &AFarmPlotActor::execInitializePlot },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AFarmPlotActor);
UClass* Z_Construct_UClass_AFarmPlotActor_NoRegister()
{
	return AFarmPlotActor::StaticClass();
}
struct Z_Construct_UClass_AFarmPlotActor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "FarmPlotActor.h" },
		{ "ModuleRelativePath", "Public/FarmPlotActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionBox_MetaData[] = {
		{ "Category", "Plot" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/FarmPlotActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlotMesh_MetaData[] = {
		{ "Category", "Plot" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/FarmPlotActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeshOffset_MetaData[] = {
		{ "Category", "Plot" },
		{ "ModuleRelativePath", "Public/FarmPlotActor.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CollisionBox;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlotMesh;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MeshOffset;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AFarmPlotActor_InitializePlot, "InitializePlot" }, // 858611722
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFarmPlotActor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFarmPlotActor_Statics::NewProp_CollisionBox = { "CollisionBox", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFarmPlotActor, CollisionBox), Z_Construct_UClass_UBoxComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionBox_MetaData), NewProp_CollisionBox_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFarmPlotActor_Statics::NewProp_PlotMesh = { "PlotMesh", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFarmPlotActor, PlotMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlotMesh_MetaData), NewProp_PlotMesh_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AFarmPlotActor_Statics::NewProp_MeshOffset = { "MeshOffset", nullptr, (EPropertyFlags)0x0010000000020005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFarmPlotActor, MeshOffset), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeshOffset_MetaData), NewProp_MeshOffset_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AFarmPlotActor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFarmPlotActor_Statics::NewProp_CollisionBox,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFarmPlotActor_Statics::NewProp_PlotMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFarmPlotActor_Statics::NewProp_MeshOffset,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AFarmPlotActor_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AFarmPlotActor_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Test_FarmPlate,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AFarmPlotActor_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AFarmPlotActor_Statics::ClassParams = {
	&AFarmPlotActor::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AFarmPlotActor_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AFarmPlotActor_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AFarmPlotActor_Statics::Class_MetaDataParams), Z_Construct_UClass_AFarmPlotActor_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AFarmPlotActor()
{
	if (!Z_Registration_Info_UClass_AFarmPlotActor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AFarmPlotActor.OuterSingleton, Z_Construct_UClass_AFarmPlotActor_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AFarmPlotActor.OuterSingleton;
}
template<> TEST_FARMPLATE_API UClass* StaticClass<AFarmPlotActor>()
{
	return AFarmPlotActor::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AFarmPlotActor);
AFarmPlotActor::~AFarmPlotActor() {}
// End Class AFarmPlotActor

// Begin Registration
struct Z_CompiledInDeferFile_FID_UnrealProjects_CppTask_Test_FarmPlate_Test_FarmPlate_Source_Test_FarmPlate_Public_FarmPlotActor_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AFarmPlotActor, AFarmPlotActor::StaticClass, TEXT("AFarmPlotActor"), &Z_Registration_Info_UClass_AFarmPlotActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AFarmPlotActor), 1695468541U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_CppTask_Test_FarmPlate_Test_FarmPlate_Source_Test_FarmPlate_Public_FarmPlotActor_h_30483561(TEXT("/Script/Test_FarmPlate"),
	Z_CompiledInDeferFile_FID_UnrealProjects_CppTask_Test_FarmPlate_Test_FarmPlate_Source_Test_FarmPlate_Public_FarmPlotActor_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_CppTask_Test_FarmPlate_Test_FarmPlate_Source_Test_FarmPlate_Public_FarmPlotActor_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
