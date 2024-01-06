// Copyright Epic Games, Inc. All Rights Reserved.

#include "AliceBaseCharacter.h"

#include "AlicePlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"

AAliceBaseCharacter::AAliceBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitInputActions();
}
// Called when the game starts or when spawned
void AAliceBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (true == IsValid(PlayerController))
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			EnhancedInputSubsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}
// Called every frame
void AAliceBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
// Called to bind functionality to input
void AAliceBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (true == IsValid(EnhancedInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAliceBaseCharacter::OnMoveAction);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AAliceBaseCharacter::OnJumpAction);
	}
}

void AAliceBaseCharacter::InitInputActions()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextAsset(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Feature/InputActions/IMC_AliceInputMappingContext.IMC_AliceInputMappingContext'"));
	if (InputMappingContextAsset.Succeeded())
	{
		InputMappingContext = InputMappingContextAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionAsset(TEXT("/Script/EnhancedInput.InputAction'/Game/Feature/InputActions/IA_AliceMove.IA_AliceMove'"));
	if (MoveActionAsset.Succeeded())
	{
		MoveAction = MoveActionAsset.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionAsset(TEXT("/Script/EnhancedInput.InputAction'/Game/Feature/InputActions/IA_AliceJump.IA_AliceJump'"));
	if (JumpActionAsset.Succeeded())
	{
		JumpAction = JumpActionAsset.Object;
	}
}

void AAliceBaseCharacter::OnMoveAction(const FInputActionInstance& Instance)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if ((Controller != nullptr))
	{
		FVector2D AxisValue2D = Instance.GetValue().Get<FVector2D>();

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector DirectionX = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector DirectionY = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(DirectionX, AxisValue2D.X);
		AddMovementInput(DirectionY, AxisValue2D.Y);
	}
}

void AAliceBaseCharacter::OnJumpAction(const FInputActionInstance& Instance)
{
	Super::Jump();
}

//#include "PlayerCharacter.h"
//
//#include "WeaponActor.h"
//#include "SniperRifleActor.h"
//#include "AssaultRifleActor.h"
//#include "ItemActor.h"
//#include "PlayerAnimInstance.h"
//#include "InventoryWidget.h"
//#include "MyGameInstance.h"
//#include "MyKeys.h"
//#include "Project_Zombie_FPSGameModeBase.h"
//#include "InGameWidget.h"
//#include "AnimalCharacter.h"
//#include "WeaponWidget.h"
//#include "WheeledVehicle_Ford.h"
//#include "MyPlayerController.h"
//
//#include "Kismet/KismetMathLibrary.h"
//#include "GameFramework/CharacterMovementComponent.h"
//#include "Sound/SoundCue.h"
//#include "PhysicalMaterials/PhysicalMaterial.h"
//#include "Components/SphereComponent.h"
//#include "Camera/CameraComponent.h"
//#include "GameFramework/WorldSettings.h"
//#include "Kismet/GameplayStatics.h"
//#include "Kismet/KismetMathLibrary.h"
//#include "Math/UnrealMathUtility.h"
//#include "Blueprint/UserWidget.h"
//#include "Perception/AIPerceptionStimuliSourceComponent.h"
//#include "Perception/AISense_Sight.h"
//#include "Components/SpotLightComponent.h"
////#include "Perception/AISense_Hearing.h"
////#include "NiagaraFunctionLibaray.h"
////#include "NiagaraComponent.h"
//
//// Sets default values
//APlayerCharacter::APlayerCharacter()
//{
//	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//	// * ī�޶�
//	BaseTurnRate = 45.f;
//	BaseLookUpRate = 45.f;
//
//	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
//	Camera->bUsePawnControlRotation = true;
//	Camera->SetupAttachment(RootComponent);
//	Camera->SetRelativeLocation(FVector(0.f, -30.f, 80.f));
//
//	// * �޽�
//	MyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MyMesh"));
//
//	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/MyBlueprint/PlayerCharacter/Arm/Meshes/Arms.Arms'"));
//	if (MeshAsset.Succeeded())
//	{
//		MyMesh->SetSkeletalMesh(MeshAsset.Object);
//	}
//	MyMesh->SetupAttachment(Camera);
//	MyMesh->SetRelativeLocation(MeshLocation);
//
//	// * �ִϸ��̼�
//	ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/MyBlueprint/PlayerCharacter/Arm/Animation/BP_ArmsAnim.BP_ArmsAnim_C'"));
//	if (AnimAsset.Succeeded())
//	{
//		MyMesh->SetAnimInstanceClass(AnimAsset.Class);
//	}
//
//	// * ��Ÿ��
//	ConstructorHelpers::FObjectFinder<UAnimMontage> MontageAsset(TEXT("AnimMontage'/Game/MyBlueprint/PlayerCharacter/Arm/Animation/BP_ArmsMontage.BP_ArmsMontage'"));
//	if (MontageAsset.Succeeded())
//	{
//		Montage = MontageAsset.Object;
//	}
//
//	// * �ΰ�����
//	Stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
//	Stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
//	//Stimulus->RegisterForSense(TSubclassOf<UAISense_Hearing>());
//	Stimulus->RegisterWithPerceptionSystem();
//
//	// * �κ��丮
//	/*ConstructorHelpers::FClassFinder<UUserWidget> InventoryWidgetAsset(TEXT("WidgetBlueprint'/Game/MyBlueprint/Widget/BP_InventoryWidget.BP_InventoryWidget_C'"));
//	if (InventoryWidgetAsset.Succeeded())
//	{
//		InventoryWidgetClass = InventoryWidgetAsset.Class;
//	}*/
//
//	// * ��ȣ�ۿ� ������Ʈ
//	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
//	InteractionSphere->AttachTo(MyMesh);
//	InteractionSphere->SetRelativeScale3D(FVector(5.f));
//	InteractionSphere->SetCollisionProfileName("OverlapAllDynamic");
//	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::StartDetection);
//	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::EndDetection);
//
//	// * ����ť
//	ConstructorHelpers::FObjectFinder<USoundCue> GrassSoundAsset(TEXT("SoundCue'/Game/MyBlueprint/PlayerCharacter/Arm/Sound/PlayerSoundCue_Grass.PlayerSoundCue_Grass'"));
//	if (GrassSoundAsset.Succeeded())
//	{
//		GrassSound = GrassSoundAsset.Object;
//	}
//
//	ConstructorHelpers::FObjectFinder<USoundCue> GroundSoundAsset(TEXT("SoundCue'/Game/MyBlueprint/PlayerCharacter/Arm/Sound/PlayerSoundCue_Ground.PlayerSoundCue_Ground'"));
//	if (GroundSoundAsset.Succeeded())
//	{
//		GroundSound = GroundSoundAsset.Object;
//	}
//
//	ConstructorHelpers::FObjectFinder<USoundCue> StoneSoundAsset(TEXT("SoundCue'/Game/MyBlueprint/PlayerCharacter/Arm/Sound/PlayerSoundCue_Stone.PlayerSoundCue_Stone'"));
//	if (StoneSoundAsset.Succeeded())
//	{
//		StoneSound = StoneSoundAsset.Object;
//	}
//
//	// * �߰����ð�
//	NightVisionLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("NightVisionLight"));
//	if (NightVisionLight != nullptr)
//	{
//		NightVisionLight->AttachTo(Camera);
//		NightVisionLight->Intensity = 3000.f;
//		NightVisionLight->AttenuationRadius = 10000.f;
//		NightVisionLight->SetVisibility(false);
//	}
//	ConstructorHelpers::FObjectFinder<UMaterial> NightVisionAsset(TEXT("Material'/Game/MyBlueprint/HuntingRifle/M_NightVision.M_NightVision'"));
//	if (NightVisionAsset.Succeeded())
//	{
//		Camera->AddOrUpdateBlendable(NightVisionAsset.Object, 1.f);
//		Camera->SetPostProcessBlendWeight(0.f);
//	}
//
//	// * �⺻ �ӵ� ����
//	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
//}
//
//// Called when the game starts or when spawned
//void APlayerCharacter::BeginPlay()
//{
//	Super::BeginPlay();
//
//	// * ���� ���� �� ���� ����
//	// ù ����� ���ݼ���
//	WeaponSR = GetWorld()->SpawnActor<ASniperRifleActor>(FVector::ZeroVector, FRotator::ZeroRotator);
//	if (WeaponSR != nullptr)
//	{
//		WeaponSR->SetOwner(this);
//		AttachToSocket(WeaponSR, PlayerSocketKeys::SRIdleSocket);
//		Weapon = WeaponSR;
//	}
//
//	WeaponAR = GetWorld()->SpawnActor<AAssaultRifleActor>(FVector::ZeroVector, FRotator::ZeroRotator);
//	if (WeaponAR != nullptr)
//	{
//		WeaponAR->SetOwner(this);
//		AttachToSocket(WeaponAR, PlayerSocketKeys::ARSocket);
//		WeaponAR->SetActorHiddenInGame(true);
//	}
//
//	// * �κ��丮 ����
//	//if (IsValid(InventoryWidgetClass))
//	//{
//	//	InventoryWidget = Cast<UInventoryWidget>(CreateWidget<UUserWidget>(GetWorld(), InventoryWidgetClass));
//	//	//InventoryWidget->SetPlayer(this);
//	//}
//}
//
//// Called every frame
//void APlayerCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//	//FRotator PlayerRotation = GetController()->GetControlRotation();
//	//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("%f, %f, %f"), PlayerRotation.Pitch, PlayerRotation.Yaw, PlayerRotation.Roll));
//
//	if (UseWeapon)
//	{
//		if (Montage != nullptr && PlayerState == EPlayerState::Idle &&
//			Weapon != nullptr && Weapon->GetCurrentBullet() > 0)
//		{
//			SetMyPlayerState(EPlayerState::Use);
//
//			FString WeaponName = Weapon->GetWeaponName();
//			MyPlayMontage(FName(FString::Printf(TEXT("Use%s"), *WeaponName)));
//			Weapon->UseWeapon();
//			//Bullets--;
//			RecoilStart();
//		}
//	}
//
//	//Mentality = FMath::Clamp(Mentality, 0.f, 100.f);
//	//Satiety = FMath::Clamp(Satiety, 0.f, 100.f);
//	//if (Satiety <= 0.f)
//	//{
//	//	// ���� �ð����� ü�� ����
//	//	SatietyHealthTime += DeltaTime;
//	//	if (SatietyHealthTime >= 3.f)
//	//	{
//	//		SatietyHealthTime = 0.f;
//	//		CurrentHp -= 4.f;
//	//	}
//	//}
//	//else
//	//	SatietyHealthTime = 0.f;
//	//Stamina = FMath::Clamp(Stamina, 0.f, 100.f);
//
//	//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("%f, %f"), MyMesh->GetRelativeLocation().X, MyMesh->GetRelativeLocation().Y));
//
//	if (IsZooming && StartZoom)
//	{
//		FVector SightLocation;
//		if (Weapon->GetWeaponType() == EWeaponType::SniperRifle)
//			SightLocation = SRSightLocation;
//		else if (Weapon->GetWeaponType() == EWeaponType::AssaultRifle)
//			SightLocation = ARSightLocation;
//
//		FVector Location = MyMesh->GetRelativeLocation();
//		Location = UKismetMathLibrary::VInterpTo(Location, SightLocation, DeltaTime, ZoomInterpSpeed);
//
//		MyMesh->SetRelativeLocation(Location);
//		if (Location == SightLocation)
//		{
//			// ������ ī�޶�� ��ȯ
//			StartZoom = false;
//			//SetActorHiddenInGame(true);
//			Weapon->ZoomIn();
//			//Weapon->SetActorHiddenInGame(true);
//			Camera->SetFieldOfView(2.f * 180.f * atan(tan(PI / 4.f) / ScopeRate) / PI);
//			//Cast<APlayerController>(GetController())->SetViewTargetWithBlend(Weapon);
//			//Cast<AProject_Zombie_FPSGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->SetScopeWidget();
//		}
//	}
//	else if (!IsZooming && StartZoom)
//	{
//		FVector Location = MyMesh->GetRelativeLocation();
//		Location = UKismetMathLibrary::VInterpTo(Location, MeshLocation, DeltaTime, ZoomInterpSpeed);
//
//		MyMesh->SetRelativeLocation(Location);
//		if (Location == MeshLocation)
//		{
//			StartZoom = false;
//		}
//	}
//
//	// * ������ ���� ����
//	if (IsZooming && !StartZoom && Weapon != nullptr)
//	{
//		Camera->SetFieldOfView(2.f * 180.f * atan(tan(PI / 4.f) / ScopeRate) / PI);
//	}
//
//	// * ��Ʈ�׼�
//	BoltActionFunction(DeltaTime);
//
//	if (Weapon->GetCurrentBullet() <= 0)
//	{
//		Reload();
//	}
//
//	// * �ݵ�
//	RecoilFunction(DeltaTime);
//
//	// * ������/����
//	if (IsZooming && !StartZoom)
//		BreathFunction(DeltaTime);
//
//	//// * ����� ��ġ > 400�ʿ� 100 �Ҹ�
//	//Satiety -= DeltaTime * 0.25f;
//
//	// * ���ο�
//	if (Slow)
//	{
//		float CurrentSpeed = GetCharacterMovement()->MaxWalkSpeed;
//		CurrentSpeed = UKismetMathLibrary::FInterpTo(CurrentSpeed, Speed, DeltaTime, 2.f);
//		if (CurrentSpeed >= Speed)
//		{
//			Slow = false;
//			CurrentSpeed = Speed;
//		}
//		GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed;
//
//		//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("%f"), CurrentSpeed));
//	}
//}
//
//// Called to bind functionality to input
//void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//	// * �Է� �Լ� ����
//	// �κ��丮�� ������� �Է�
//	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &APlayerCharacter::Inventory);
//	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APlayerCharacter::Pause);
//	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
//	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
//	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
//
//	// �κ��丮�� ������ ������ �ȵǴ� �Է�
//	PlayerInputComponent->BindAxis("TurnAtRate", this, &APlayerCharacter::TurnAtRate);
//	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpRate);
//	PlayerInputComponent->BindAxis("Zoom", this, &APlayerCharacter::Zoom);
//
//	PlayerInputComponent->BindAction("Use", IE_Pressed, this, &APlayerCharacter::Use);
//	PlayerInputComponent->BindAction("Use", IE_Released, this, &APlayerCharacter::BoltAction);
//	PlayerInputComponent->BindAction("ZoomOn", IE_Pressed, this, &APlayerCharacter::ZoomOn);
//	//PlayerInputComponent->BindAction("ZoomOn", IE_Released, this, &APlayerCharacter::ZoomOn);
//	PlayerInputComponent->BindAction("MeleeAttack", IE_Pressed, this, &APlayerCharacter::MeleeAttack);
//	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCharacter::Reload);
//	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
//
//	PlayerInputComponent->BindAction("ZeroPointUp", IE_Pressed, this, &APlayerCharacter::ZeroPointUp);
//	PlayerInputComponent->BindAction("ZeroPointDown", IE_Pressed, this, &APlayerCharacter::ZeroPointDown);
//
//	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayerCharacter::Run);
//	PlayerInputComponent->BindAction("Run", IE_Released, this, &APlayerCharacter::Run);
//
//	PlayerInputComponent->BindAction("SR", IE_Pressed, this, &APlayerCharacter::ChangeToSR);
//	PlayerInputComponent->BindAction("AR", IE_Pressed, this, &APlayerCharacter::ChangeToAR);
//
//	PlayerInputComponent->BindAction("NightVision", IE_Pressed, this, &APlayerCharacter::NightVisionOn);
//}
//
//void APlayerCharacter::BoltActionFunction(float DeltaTime)
//{
//	if (bBoltAction)
//	{
//		// ���� ��Ÿ�ְ� ������ ����
//		if (FireEnd)
//		{
//			MyPlayMontage(TEXT("BoltAction"));
//			if (Weapon != nullptr)
//				Weapon->BoltAction();
//			FireEnd = false;
//		}
//
//		// * �� ���� ���ݽ� �� ����
//		if (IsZooming && PlayerState == EPlayerState::Use)
//		{
//			ZoomOn();
//			//ReturnToZoom = true;
//		}
//		else if (PlayerState == EPlayerState::Idle && Weapon->GetCurrentBullet() > 0)
//		{
//			/*if (ReturnToZoom)
//			{
//				ZoomOn();
//				ReturnToZoom = false;
//			}*/
//			bBoltAction = false;
//		}
//	}
//}
//
//void APlayerCharacter::RecoilStart()
//{
//	RecoilStartRot = GetControlRotation();
//
//	bRecoil = true;
//	bRecoilRecovery = false;
//
//	RecoilTime = 0.f;
//}
//
//void APlayerCharacter::RecoveryStart()
//{
//	bRecoilRecovery = true;
//
//	RecoveryTime = 0.f;
//}
//
//void APlayerCharacter::RecoilReset()
//{
//	bRecoil = false;
//	bRecoilRecovery = false;
//	RecoilTime = 0.f;
//	RecoveryTime = 0.f;
//}
//
//void APlayerCharacter::RecoilFunction(float DeltaTime)
//{
//	// * �ݵ�
//	if (bRecoil)
//	{
//		RecoilTime += DeltaTime;
//
//		// ��ȭ ����
//		GetController()->SetControlRotation(GetControlRotation() + RecoilDeltaRot * (DeltaTime / 0.1f));
//		// �¿�� ���� ��ȭ
//		float LRYaw = (FMath::RandRange(0, 1) == 0 ? 2.f : -2.f);
//		GetController()->SetControlRotation(GetControlRotation() + FRotator(0.f, LRYaw, 0.f) * (DeltaTime / 0.1f));
//
//		// ��ȭ �� ���� �������� pitch�� ���� ��� ��� ����
//		if (GetControlRotation().Pitch < RecoilStartRot.Pitch)
//			RecoilReset();
//
//		// 0.1�ʰ� ��ȭ �� ȸ�� ����
//		if (RecoilTime >= 0.1f)
//		{
//			bRecoil = false;
//			RecoveryStart();
//		}
//	}
//	else if (bRecoilRecovery)
//	{
//		RecoveryTime += DeltaTime;
//
//		// ��ȭ ����
//		GetController()->SetControlRotation(GetControlRotation() - RecoilDeltaRot * (DeltaTime / 0.4f));
//
//		// ��ȭ �� ���� �������� pitch�� ���� ��� ��� ����
//		if (GetControlRotation().Pitch < RecoilStartRot.Pitch)
//			RecoilReset();
//
//		// 0.4�ʰ� ��ȭ �� ����
//		if (RecoveryTime >= 0.4f)
//		{
//			bRecoilRecovery = false;
//		}
//	}
//}
//
//void APlayerCharacter::BreathFunction(float DeltaTime)
//{
//	if (BreathingAmplitude > 0.1f && HoldingBreath)
//		BreathingAmplitude -= DeltaTime * 0.5f;
//	else if (BreathingAmplitude < 1.f && !HoldingBreath)
//		BreathingAmplitude += DeltaTime * 0.5f;
//
//	BreathingAmplitude = FMath::Clamp(BreathingAmplitude, 0.1f, 1.f);
//
//	float before = 0.5f * sin(BreathingTime) * BreathingAmplitude;
//	BreathingTime += 2.f * DeltaTime;
//	if (BreathingTime >= 2 * PI)
//		BreathingTime -= 2 * PI;
//	float after = 0.5f * sin(BreathingTime) * BreathingAmplitude;
//
//	FRotator DeltaRot(after - before, 0.f, 0.f);
//	// StartRotation ���� �����Լ��� ���� ������
//	GetController()->SetControlRotation(GetControlRotation() + DeltaRot);
//}
//
//void APlayerCharacter::Inventory()
//{
//	UInventoryWidget* InventoryWidget = Cast<AMyPlayerController>(GetController())->GetInventoryWidget();
//
//	if (InventoryWidget != nullptr)
//	{
//		if (!IsInventory)
//		{
//			if (IsZooming)
//				ZoomOn();
//			InventoryWidget->AddToViewport(); // ����Ʈ�� ������
//			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
//			FInputModeGameAndUI InputMode; //����� �Է�ó�� ����ü
//			InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
//			//�Է¿� ����� ���� ����
//			InputMode.SetHideCursorDuringCapture(false);
//			//����Ʈ�� ���콺�� ĸ���Ҷ� ������
//			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameAndUI(InputMode));
//			IsInventory = true;
//
//			RefreshUI();
//		}
//		else if (IsInventory)
//		{
//			APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
//			playerController->SetShowMouseCursor(false);
//			playerController->SetInputMode(FInputModeGameOnly());
//			//FInputModeGameOnly : �Է��� ���ӿ��� ����
//			InventoryWidget->RemoveFromViewport(); //����Ʈ���� ���� ����
//			//InventoryWidget->RemoveFromParnet(); //������ҿ��� ����
//			IsInventory = false;
//		}
//	}
//}
//
//void APlayerCharacter::Pause()
//{
//	auto GameModeBase = Cast<AProject_Zombie_FPSGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
//	if (GameModeBase != nullptr)
//	{
//		GameModeBase->SetPauseWidget();
//	}
//}
//
//void APlayerCharacter::Interact()
//{
//	// ��ȣ�ۿ��� ������ ��� �繰�� ��ȣ�ۿ� �� �� �ֵ���
//	// �������̽��� ����� ��
//	if (ActorForInteract != nullptr)
//	{
//		IInteractInterface::Execute_Interaction(ActorForInteract);
//		RefreshUI();
//	}
//}
//
//void APlayerCharacter::MoveForward(float AxisValue)
//{
//	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController());
//
//	if ((Controller != nullptr) && (AxisValue != 0.f))
//	{
//		const FRotator Rotation = Controller->GetControlRotation();
//		const FRotator YawRotation(0, Rotation.Yaw, 0);
//
//		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
//		AddMovementInput(Direction, AxisValue);
//
//		// �����϶����� ���¹̳� ����
//		// �����غ��� 0.01 ���ϸ� �뷫 100m�� 18����
//		PlayerController->SetStamina(PlayerController->GetStamina() - FMath::Abs(AxisValue) * 0.01f);
//	}
//}
//
//void APlayerCharacter::MoveRight(float AxisValue)
//{
//	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController());
//
//	if ((Controller != nullptr) && (AxisValue != 0.f))
//	{
//		const FRotator Rotation = Controller->GetControlRotation();
//		const FRotator YawRotation(0, Rotation.Yaw, 0);
//
//		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
//		AddMovementInput(Direction, AxisValue);
//
//		PlayerController->SetStamina(PlayerController->GetStamina() - FMath::Abs(AxisValue) * 0.01f);
//	}
//}
//
//void APlayerCharacter::TurnAtRate(float AxisValue)
//{
//	if (!IsInventory)
//		AddControllerYawInput(AxisValue * BaseTurnRate * GetWorld()->GetDeltaSeconds());
//}
//
//void APlayerCharacter::LookUpRate(float AxisValue)
//{
//	if (!IsInventory)
//		AddControllerPitchInput(AxisValue * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
//}
//
//void APlayerCharacter::Use()
//{
//	if (PlayerState == EPlayerState::Idle && !IsInventory &&
//		Weapon != nullptr && Weapon->GetCurrentBullet() > 0)
//		UseWeapon = true;
//}
//
//void APlayerCharacter::BoltAction()
//{
//	UseWeapon = false;
//
//	if (Weapon != nullptr && Weapon->GetWeaponType() == EWeaponType::SniperRifle)
//	{
//		bBoltAction = true;
//	}
//}
//
//void APlayerCharacter::ZoomOn()
//{
//	StartZoom = true;
//
//	// ���ذ� ���°� �ƴ� ��
//	if (!IsZooming && !IsInventory)
//	{
//		IsZooming = true;
//		BreathingTime = 0.f;
//		//Cast<AProject_Zombie_FPSGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->SetScopeWidget();
//	}
//	else if (IsZooming && !IsInventory) // ���ذ� ���¿���
//	{
//		IsZooming = false;
//		// ���� �����⵵ �ʱ�ȭ
//		HoldingBreath = false;
//		// �� ���� pitch�� �����ֱ�
//		GetController()->SetControlRotation(GetControlRotation() - FRotator(0.5f * sin(BreathingTime), 0.f, 0.f));
//
//		//Cast<AProject_Zombie_FPSGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->RemoveScopeWidget();
//		//SetActorHiddenInGame(false);
//		Weapon->ZoomOut();
//		//Weapon->SetActorHiddenInGame(false);
//		Camera->SetFieldOfView(90.f);
//		// ī�޶� �ű��
//		//Cast<APlayerController>(GetController())->SetViewTargetWithBlend(this);
//	}
//}
//
//void APlayerCharacter::Zoom(float AxisValue)
//{
//	// ���ذ�� �� ���¿����� ����
//	if (IsZooming)
//	{
//		// �ӵ��� �ʹ� ������ �ʰ� 0.4 �����ֱ�
//		ScopeRate += AxisValue * 0.4f;
//		// ������ �ּ� �ִ�ġ��ŭ�� ����
//		if (Weapon != nullptr)
//		{
//			ScopeRate = FMath::Clamp(ScopeRate, Weapon->GetMinZoomRate(), Weapon->GetMaxZoomRate());
//		}
//	}
//}
//
//void APlayerCharacter::MeleeAttack()
//{
//	if (Montage != nullptr && PlayerState == EPlayerState::Idle && !IsInventory)
//	{
//		SetMyPlayerState(EPlayerState::Attack);
//
//		if (Weapon != nullptr)
//		{
//			FString WeaponName = Weapon->GetWeaponName();
//			MyPlayMontage(FName(FString::Printf(TEXT("MeleeAttack%s"), *WeaponName)));
//			Weapon->MeleeAttack();
//		}
//	}
//}
//
//void APlayerCharacter::Reload()
//{
//	if (Montage != nullptr && PlayerState == EPlayerState::Idle &&
//		Weapon != nullptr &&
//		Weapon->GetRemainBullet() > 0 &&
//		Weapon->GetCurrentBullet() < Weapon->GetMaxBullet() &&
//		!IsZooming && !IsInventory)
//	{
//		SetMyPlayerState(EPlayerState::Reload);
//
//		FString WeaponName = Weapon->GetWeaponName();
//		MyPlayMontage(FName(FString::Printf(TEXT("Reload%s"), *WeaponName)));
//		Weapon->ReloadWeapon();
//	}
//}
//
//void APlayerCharacter::ZeroPointUp()
//{
//	if (IsZooming)
//	{
//		ZeroPoint += 100.f;
//		ZeroPoint = FMath::Clamp(ZeroPoint, 100.f, 400.f);
//		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("ZeroPoint : %f"), ZeroPoint));
//	}
//}
//
//void APlayerCharacter::ZeroPointDown()
//{
//	if (IsZooming)
//	{
//		ZeroPoint -= 100.f;
//		ZeroPoint = FMath::Clamp(ZeroPoint, 100.f, 400.f);
//		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("ZeroPoint : %f"), ZeroPoint));
//	}
//}
//
//void APlayerCharacter::Run()
//{
//	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController());
//
//	if (IsZooming && WeaponType == EWeaponType::SniperRifle) // �������� ������ �� ���¿��� ������ ���
//	{
//		HoldingBreath = !HoldingBreath;
//	}
//	else if (!IsInventory && PlayerController->GetStamina() > 0.f) // �ƴ� ��� �ȱ�/�޸��� ��ȯ
//	{
//		if (IsRun)
//		{
//			IsRun = false;
//			GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
//		}
//		else
//		{
//			IsRun = true;
//			GetCharacterMovement()->MaxWalkSpeed = Speed;
//		}
//	}
//}
//
//void APlayerCharacter::ChangeToSR()
//{
//	if (Weapon != nullptr && Weapon != WeaponSR &&
//		PlayerState == EPlayerState::Idle && !IsInventory)
//	{
//		if (IsZooming)
//			ZoomOn();
//
//		SetMyPlayerState(EPlayerState::HideWeapon);
//
//		HideWeapon();
//	}
//}
//
//void APlayerCharacter::ChangeToAR()
//{
//	if (Weapon != nullptr && Weapon != WeaponAR &&
//		PlayerState == EPlayerState::Idle && !IsInventory)
//	{
//		if (IsZooming)
//			ZoomOn();
//
//		SetMyPlayerState(EPlayerState::HideWeapon);
//
//		HideWeapon();
//	}
//}
//
//void APlayerCharacter::NightVisionOn()
//{
//	if (!IsNightVision)
//	{
//		IsNightVision = true;
//		Camera->SetPostProcessBlendWeight(1.f);
//		NightVisionLight->SetVisibility(true);
//	}
//	else
//	{
//		IsNightVision = false;
//		Camera->SetPostProcessBlendWeight(0.f);
//		NightVisionLight->SetVisibility(false);
//	}
//}
//
//float APlayerCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
//	AController* EventInstigator, AActor* DamageCauser)
//{
//	const float damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
//
//	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController());
//	if (PlayerController == nullptr)
//		return damage;
//
//	PlayerController->SetCurrentHp(PlayerController->GetCurrentHp() - damage);
//
//	if (PlayerController->GetCurrentHp() <= 0.f)
//	{
//		auto GameModeBase = Cast<AProject_Zombie_FPSGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
//		if (GameModeBase != nullptr)
//		{
//			GameModeBase->Gameover();
//		}
//
//		// ��Ʈ�ѷ� ���� ����
//		GetController()->UnPossess();
//	}
//
//	return damage;
//}
//
//float APlayerCharacter::MyPlayMontage(FName SectionName, float speed)
//{
//	float ret = 0.f;
//
//	UPlayerAnimInstance* MyAnimInstance = Cast<UPlayerAnimInstance>(MyMesh->GetAnimInstance());
//	if (MyAnimInstance != nullptr)
//	{
//		ret = MyAnimInstance->Montage_Play(Montage, speed);
//		MyAnimInstance->Montage_JumpToSection(SectionName);
//	}
//
//	return ret;
//}
//
//void APlayerCharacter::StartDetection(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (OtherActor != nullptr && OtherActor != this)
//	{
//		AItemActor* Item = Cast<AItemActor>(OtherActor);
//		if (Item != nullptr)
//			AddDetectedItem(Item);
//	}
//
//	TArray<AActor*> Actors;
//	InteractionSphere->GetOverlappingActors(Actors);
//
//	for (auto actor : Actors)
//	{
//		if (actor != this && actor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
//		{
//			ActorForInteract = actor;
//
//			AAnimalCharacter* Animal = Cast<AAnimalCharacter>(actor);
//
//			if (InGameWidget != nullptr)
//			{
//				// ������ �׾��� ��쿡�� ��ȣ�ۿ� Ű On ���־����
//				if (Animal != nullptr && Animal->GetLife())
//				{
//					// Alive animal > None!
//				}
//				else
//					InGameWidget->SetInteractWidgetVisibility(ESlateVisibility::Visible);
//			}
//
//			break;
//		}
//	}
//}
//
//void APlayerCharacter::EndDetection(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	if (OtherActor != nullptr && OtherActor != this)
//	{
//		AItemActor* Item = Cast<AItemActor>(OtherActor);
//		if (Item != nullptr)
//			RemoveDetectedItem(Item);
//	}
//
//	ActorForInteract = nullptr;
//
//	TArray<AActor*> Actors;
//	InteractionSphere->GetOverlappingActors(Actors);
//
//	for (auto actor : Actors)
//	{
//		if (actor != this && actor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
//		{
//			ActorForInteract = actor;
//
//			break;
//		}
//	}
//
//	if (InGameWidget != nullptr)
//		InGameWidget->SetInteractWidgetVisibility(ESlateVisibility::Hidden);
//}
//
//void APlayerCharacter::AttachToSocket(AActor* Actor, FName SocketName)
//{
//	Actor->AttachToComponent(MyMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
//}
//
//void APlayerCharacter::SetMyPlayerState(EPlayerState state)
//{
//	PlayerState = state;
//}
//
//void APlayerCharacter::AddDetectedItem(AItemActor* Item)
//{
//	UInventoryWidget* InventoryWidget = Cast<AMyPlayerController>(GetController())->GetInventoryWidget();
//
//	if (Item != nullptr && InventoryWidget != nullptr)
//	{
//		DetectedItems.Add(Item);
//
//		InventoryWidget->UpdateDetectedItemList();
//	}
//}
//
//void APlayerCharacter::RemoveDetectedItem(AItemActor* Item)
//{
//	UInventoryWidget* InventoryWidget = Cast<AMyPlayerController>(GetController())->GetInventoryWidget();
//
//	if (Item != nullptr && DetectedItems.Num() > 0 && InventoryWidget != nullptr)
//	{
//		int32 index = DetectedItems.Find(Item);
//		if (index != -1)
//		{
//			DetectedItems.RemoveAt(index);
//
//			InventoryWidget->UpdateDetectedItemList();
//		}
//	}
//}
//
//void APlayerCharacter::RefreshUI()
//{
//	if (GetController() == nullptr)
//		return;
//	UInventoryWidget* InventoryWidget = nullptr;
//
//	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController());
//	if (PlayerController != nullptr)
//		InventoryWidget = PlayerController->GetInventoryWidget();
//
//	if (InventoryWidget != nullptr)
//	{
//		InventoryWidget->UpdateDetectedItemList();
//		InventoryWidget->UpdateItemList();
//
//		if (IsInventory)
//		{
//			FInputModeGameAndUI InputMode;
//			InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
//			// false > ���콺 Ŭ�� �� Ŀ���� �Ȼ����
//			InputMode.SetHideCursorDuringCapture(false);
//			//UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(InputMode);
//			Cast<APlayerController>(GetController())->SetInputMode(InputMode);
//		}
//	}
//}
//
//void APlayerCharacter::HideWeapon()
//{
//	if (Montage != nullptr && Weapon != nullptr)
//	{
//		FString WeaponName = Weapon->GetWeaponName();
//		MyPlayMontage(FName(FString::Printf(TEXT("Hide%s"), *WeaponName)));
//		Weapon->HideWeapon();
//	}
//}
//
//void APlayerCharacter::ReadyWeapon()
//{
//	if (PlayerState == EPlayerState::HideWeapon)
//	{
//		SetMyPlayerState(EPlayerState::ReadyWeapon);
//
//		Weapon->SetActorHiddenInGame(true);
//
//		// SR�̾��ٸ� AR������
//		if (Weapon->GetWeaponType() == EWeaponType::SniperRifle)
//			Weapon = WeaponAR;
//		else if (Weapon->GetWeaponType() == EWeaponType::AssaultRifle)
//			Weapon = WeaponSR;
//
//		Weapon->SetActorHiddenInGame(false);
//		WeaponType = Weapon->GetWeaponType();
//		//FString WeaponName = Weapon->GetWeaponName();
//		//MyPlayMontage(FName(FString::Printf(TEXT("Ready%s"), *WeaponName)));
//		Weapon->ReadyWeapon();
//		// ������ ���� �̹��� ����
//		AProject_Zombie_FPSGameModeBase* GameMode = Cast<AProject_Zombie_FPSGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
//		if (GameMode != nullptr)
//			GameMode->ChangeWeaponImage(Weapon->GetTexture(), Weapon->GetTexturePos(), Weapon->GetTextureSize());
//	}
//}
//
//void APlayerCharacter::FootStep()
//{
//	FVector ActorLocation = GetActorLocation();
//	FVector Start(ActorLocation.X, ActorLocation.Y, ActorLocation.Z);
//	FVector End(ActorLocation.X, ActorLocation.Y, ActorLocation.Z - 150.f);
//
//	FHitResult HitResult;
//	TArray<AActor*> ActorToIgnore;
//	EDrawDebugTrace::Type DebugType = EDrawDebugTrace::None;
//
//	bool bTrace = UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End,
//		UEngineTypes::ConvertToTraceType(ECC_Visibility), true, ActorToIgnore,
//		DebugType, HitResult, true);
//
//	USoundCue* FootStepSound = nullptr;
//	// ���� ���� �����ֱ�
//	if (HitResult.PhysMaterial.Get() != nullptr)
//	{
//		switch (HitResult.PhysMaterial.Get()->SurfaceType)
//		{
//		case SurfaceType1: // Grass
//			FootStepSound = GrassSound;
//			break;
//		case SurfaceType2: // Ground
//			FootStepSound = GroundSound;
//			break;
//		case SurfaceType3: // Stone
//			FootStepSound = StoneSound;
//			break;
//		case SurfaceType4: // Water
//			FootStepSound = WaterSound;
//			break;
//		default:
//			FootStepSound = GrassSound;
//			break;
//		}
//	}
//
//	// ���� ���
//	if (bTrace && FootStepSound != nullptr)
//		UGameplayStatics::PlaySound2D(GetWorld(), FootStepSound);
//
//	// AI ������ ���� ������ �߻�
//	MakeNoise(1.f, this);
//}
//
//void APlayerCharacter::SlowCharacter()
//{
//	Slow = true;
//	GetCharacterMovement()->MaxWalkSpeed = 10.f;
//}
//
////void APlayerCharacter::UseItem(FItemData itemData)
////{
////	CurrentHp += itemData.Hp;
////	Mentality += itemData.Mentality;
////	Satiety += itemData.Satiety;
////	Stamina += itemData.Stamina;
////}
