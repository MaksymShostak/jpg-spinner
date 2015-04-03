﻿//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

//
// Scenario1.xaml.cpp
// Implementation of the Scenario1 class
//

#include "pch.h"
#include "Scenario_AfterPick.xaml.h"
#include "ItemViewer.xaml.h"

using namespace JPG_Spinner;

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;

static HRESULT PROPVAR_ConvertNumber(
	PROPVARIANT *pv,
	int dest_bits,
	BOOL dest_signed,
	LONGLONG *res
	)
{
	BOOL src_signed;

	switch (pv->vt)
	{
	case VT_I1:
		src_signed = TRUE;
		*res = pv->cVal;
		break;
	case VT_UI1:
		src_signed = FALSE;
		*res = pv->bVal;
		break;
	case VT_I2:
		src_signed = TRUE;
		*res = pv->iVal;
		break;
	case VT_UI2:
		src_signed = FALSE;
		*res = pv->uiVal;
		break;
	case VT_I4:
		src_signed = TRUE;
		*res = pv->lVal;
		break;
	case VT_UI4:
		src_signed = FALSE;
		*res = pv->ulVal;
		break;
	case VT_I8:
		src_signed = TRUE;
		*res = pv->hVal.QuadPart;
		break;
	case VT_UI8:
		src_signed = FALSE;
		*res = pv->uhVal.QuadPart;
		break;
	case VT_EMPTY:
		src_signed = FALSE;
		*res = 0;
		break;
	default:
		return E_NOTIMPL;
	}

	if (*res < 0 && src_signed != dest_signed)
		return HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW);

	if (dest_bits < 64)
	{
		if (dest_signed)
		{
			if (*res >= ((LONGLONG)1 << (dest_bits - 1)) ||
				*res < ((LONGLONG)-1 << (dest_bits - 1)))
				return HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW);
		}
		else
		{
			if ((ULONGLONG)(*res) >= ((ULONGLONG)1 << dest_bits))
				return HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW);
		}
	}

	return S_OK;
}

HRESULT WINAPI PropVariantToUInt16(PROPVARIANT *propvarIn, USHORT *ret)
{
	LONGLONG res;
	HRESULT hr;

	hr = PROPVAR_ConvertNumber(propvarIn, 16, FALSE, &res);
	if (SUCCEEDED(hr)) *ret = (USHORT)res;
	return hr;
}

HRESULT GetJPEGOrientationFlag(IStream * FileStream, USHORT &OrientationFlag, IWICImagingFactory * pIWICImagingFactory)
{
	Microsoft::WRL::ComPtr<IWICBitmapDecoder> pDecoder;
	Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> pSource;
	GUID guidContainerFormat;

	HRESULT hr = pIWICImagingFactory->CreateDecoderFromStream(
		FileStream,
		NULL,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
		);

	if (FAILED(hr)) // try to load without caching metadata
	{
		hr = pIWICImagingFactory->CreateDecoderFromStream(
			FileStream,
			NULL,
			WICDecodeMetadataCacheOnDemand,
			&pDecoder
			);
	}

	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetContainerFormat(&guidContainerFormat);
	}

	if (SUCCEEDED(hr))
	{
		if (guidContainerFormat != GUID_ContainerFormatJpeg)
		{
			return E_FAIL;
		}
	}

	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		Microsoft::WRL::ComPtr<IWICMetadataQueryReader> pQueryReader;

		PROPVARIANT propvariantOrientationFlag = { 0 };
		PropVariantInit(&propvariantOrientationFlag);

		hr = pSource->GetMetadataQueryReader(&pQueryReader);

		if (SUCCEEDED(hr))
		{
			hr = pQueryReader->GetMetadataByName(L"/app1/ifd/{ushort=274}", &propvariantOrientationFlag);
			// if cannot find EXIF orientation try xmp
			if (FAILED(hr))
			{
				hr = pQueryReader->GetMetadataByName(L"/xmp/tiff:Orientation", &propvariantOrientationFlag);
			}
		}

		if (SUCCEEDED(hr))
		{
			hr = PropVariantToUInt16(&propvariantOrientationFlag, &OrientationFlag);
		}

		PropVariantClear(&propvariantOrientationFlag);
	}

	return hr;
}

HRESULT SetJPEGOrientationFlag(IStream * FileStream, const USHORT OrientationFlag, IWICImagingFactory * pIWICImagingFactory)
{
	Microsoft::WRL::ComPtr<IWICBitmapDecoder> pDecoder;
	Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> pSource;
	GUID guidContainerFormat;

	HRESULT hr = pIWICImagingFactory->CreateDecoderFromStream(
		FileStream,
		NULL,
		WICDecodeMetadataCacheOnDemand, // A decoder must be created using the WICDecodeOptions value WICDecodeMetadataCacheOnDemand to perform in-place metadata updates
		&pDecoder
		);

	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetContainerFormat(&guidContainerFormat);
	}

	if (SUCCEEDED(hr))
	{
		if (guidContainerFormat != GUID_ContainerFormatJpeg)
		{
			return E_FAIL;
		}
	}

	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		Microsoft::WRL::ComPtr<IWICFastMetadataEncoder> pFME;
		Microsoft::WRL::ComPtr<IWICMetadataQueryWriter> pFMEQW;

		hr = pIWICImagingFactory->CreateFastMetadataEncoderFromFrameDecode(pSource.Get(), &pFME);

		if (SUCCEEDED(hr))
		{
			hr = pFME->GetMetadataQueryWriter(&pFMEQW);
		}

		if (SUCCEEDED(hr))
		{
			Microsoft::WRL::ComPtr<IWICMetadataQueryReader> pQueryReader;
			PROPVARIANT propvariantOrientationFlag = { 0 };
			PROPVARIANT value = { 0 };

			PropVariantInit(&propvariantOrientationFlag);
			PropVariantInit(&value);

			value.vt = VT_UI2;
			value.uiVal = OrientationFlag;

			hr = pSource->GetMetadataQueryReader(&pQueryReader);

			if (SUCCEEDED(hr))
			{
				HRESULT hrEXIF = S_OK;

				hr = pQueryReader->GetMetadataByName(L"/app1/ifd/{ushort=274}", &propvariantOrientationFlag);

				if (SUCCEEDED(hr) && propvariantOrientationFlag.vt != VT_EMPTY)
				{
					hr = pFMEQW->SetMetadataByName(L"/app1/ifd/{ushort=274}", &value);
				}

				hrEXIF = hr;

				PropVariantClear(&propvariantOrientationFlag);

				hr = pQueryReader->GetMetadataByName(L"/xmp/tiff:Orientation", &propvariantOrientationFlag);

				// usually WINCODEC_ERR_PROPERTYNOTFOUND == hr here
				if (SUCCEEDED(hr) && propvariantOrientationFlag.vt != VT_EMPTY)
				{
					hr = pFMEQW->SetMetadataByName(L"/xmp/tiff:Orientation", &value);
				}
				// if the XMP update failed, then 
				else
				{
					hr = hrEXIF;
				}
			}

			PropVariantClear(&propvariantOrientationFlag);
			PropVariantClear(&value);
		}

		if (SUCCEEDED(hr))
		{
			hr = pFME->Commit();
		}
	}

	return hr;
}

static Platform::String^ GetUUID()
{
	GUID result;
	HRESULT hr = CoCreateGuid(&result);

	if (SUCCEEDED(hr))
	{
		Platform::Guid gd(result);
		return gd.ToString();
	}

	throw Platform::Exception::CreateException(hr);
}

HRESULT ChangeOrientation(
	Windows::Storage::StorageFile^ originalFile,
	FILE * fp,
	USHORT OrientationFlag,
	IWICImagingFactory * pIWICImagingFactory,
	BOOL Trim = FALSE,
	BOOL Progressive = TRUE
	)
{
	struct jpeg_decompress_struct srcinfo;
	struct jpeg_compress_struct dstinfo;
	struct jpeg_error_mgr jsrcerr, jdsterr;

	jvirt_barray_ptr * src_coef_arrays;
	jvirt_barray_ptr * dst_coef_arrays;

	/* We assume all-in-memory processing and can therefore use only a
	* single file pointer for sequential input and output operation.
	*/

	jpeg_transform_info transformoption;
	JCOPY_OPTION copyoption = JCOPYOPT_ALL;

	switch (OrientationFlag) {
	case 2U:
	{
		transformoption.transform = JXFORM_FLIP_H;
	}
	break;
	case 3U:
	{
		transformoption.transform = JXFORM_ROT_180;
	}
	break;
	case 4U:
	{
		transformoption.transform = JXFORM_FLIP_V;
	}
	break;
	case 5U:
	{
		transformoption.transform = JXFORM_TRANSPOSE;
	}
	break;
	case 6U:
	{
		transformoption.transform = JXFORM_ROT_90;
	}
	break;
	case 7U:
	{
		transformoption.transform = JXFORM_TRANSVERSE;
	}
	break;
	case 8U:
	{
		transformoption.transform = JXFORM_ROT_270;
	}
	break;
	default:
	{
		transformoption.transform = JXFORM_NONE;
	}
	break;
	}

	transformoption.perfect = (Trim == TRUE) ? FALSE : TRUE;
	transformoption.trim = (Trim == TRUE) ? TRUE : FALSE;
	transformoption.force_grayscale = FALSE;
	transformoption.crop = FALSE;

	// Initialize the JPEG decompression object with default error handling
	srcinfo.err = jpeg_std_error(&jsrcerr);
	jpeg_create_decompress(&srcinfo);
	// Initialize the JPEG compression object with default error handling
	dstinfo.err = jpeg_std_error(&jdsterr);
	jpeg_create_compress(&dstinfo);

	if (Progressive)
	{
		// Set progressive mode (saves space but is slower)
		jpeg_simple_progression(&dstinfo);
	}

	// Note: we assume only the decompression object will have virtual arrays

	dstinfo.optimize_coding = TRUE;
	dstinfo.err->trace_level = 0;
	//srcinfo.mem->max_memory_to_use = dstinfo.mem->max_memory_to_use;

	// Specify data source for decompression
	jpeg_stdio_src(&srcinfo, fp);

	// Enable saving of extra markers that we want to copy
	jcopy_markers_setup(&srcinfo, copyoption);

	// Read file header
	(void)jpeg_read_header(&srcinfo, TRUE);

	if (!jtransform_request_workspace(&srcinfo, &transformoption))
	{
		fclose(fp);
		return HRESULT_FROM_WIN32(ERROR_INVALID_DATA);
	}

	// Read source file as DCT coefficients
	src_coef_arrays = jpeg_read_coefficients(&srcinfo);

	// Initialize destination compression parameters from source values
	jpeg_copy_critical_parameters(&srcinfo, &dstinfo);

	/* Adjust destination parameters if required by transform options;
	* also find out which set of coefficient arrays will hold the output.
	*/
	dst_coef_arrays = jtransform_adjust_parameters(&srcinfo, &dstinfo, src_coef_arrays, &transformoption);

	// Close input file
	/* Note: we assume that jpeg_read_coefficients consumed all input
	* until JPEG_REACHED_EOI, and that jpeg_finish_decompress will
	* only consume more while (! cinfo->inputctl->eoi_reached).
	* We cannot call jpeg_finish_decompress here since we still need the
	* virtual arrays allocated from the source object for processing.
	*/
	fclose(fp);

	// Creates the new temp file to write to
	Windows::Storage::StorageFolder^ temporaryFolder = Windows::Storage::ApplicationData::Current->TemporaryFolder;

	Platform::String^ tempFileName = temporaryFolder->Path + "\\" + GetUUID();

	HANDLE hTempFile = INVALID_HANDLE_VALUE;

	CREATEFILE2_EXTENDED_PARAMETERS extendedParams = { 0 };
	extendedParams.dwSize = sizeof(CREATEFILE2_EXTENDED_PARAMETERS);
	extendedParams.dwFileAttributes = FILE_ATTRIBUTE_TEMPORARY;
	extendedParams.dwFileFlags = FILE_FLAG_RANDOM_ACCESS;
	extendedParams.dwSecurityQosFlags = SECURITY_ANONYMOUS;
	extendedParams.lpSecurityAttributes = nullptr;
	extendedParams.hTemplateFile = nullptr;

	hTempFile = CreateFile2(
		tempFileName->Data(), // file name 
		GENERIC_READ | GENERIC_WRITE, // open for read/write 
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		CREATE_ALWAYS,
		&extendedParams
		);

	if (INVALID_HANDLE_VALUE == hTempFile)
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	// Open the output file from the handle
	int fd = _open_osfhandle((intptr_t)hTempFile, _O_APPEND | _O_RDONLY);

	if (-1 == fd)
	{
		CloseHandle(hTempFile);
		return E_FAIL;
	}

	fp = _fdopen(fd, "wb");

	if (0 == fp)
	{
		_close(fd); // Also calls CloseHandle()
		return HRESULT_FROM_WIN32(ERROR_CANNOT_MAKE);
	}

	// Specify data destination for compression
	jpeg_stdio_dest(&dstinfo, fp);

	// Start compressor (note no image data is actually written here)
	jpeg_write_coefficients(&dstinfo, dst_coef_arrays);

	// Copy to the output file any extra markers that we want to preserve
	jcopy_markers_execute(&srcinfo, &dstinfo, copyoption);

	// Execute image transformation, if any
	jtransform_execute_transformation(&srcinfo, &dstinfo, src_coef_arrays, &transformoption);

	// Finish compression and release memory
	jpeg_finish_compress(&dstinfo);
	jpeg_destroy_compress(&dstinfo);
	(void)jpeg_finish_decompress(&srcinfo);
	jpeg_destroy_decompress(&srcinfo);

	// Close output file, also calls _close()
	fclose(fp);

	auto getFileFromPathAsyncTask = concurrency::create_task(Windows::Storage::StorageFile::GetFileFromPathAsync(tempFileName));

	getFileFromPathAsyncTask.then([pIWICImagingFactory, originalFile](Windows::Storage::StorageFile^ tempFile)
	{
		auto openAsyncTask = concurrency::create_task(tempFile->OpenAsync(Windows::Storage::FileAccessMode::ReadWrite));

		openAsyncTask.then([tempFile, pIWICImagingFactory, originalFile](Windows::Storage::Streams::IRandomAccessStream^ fileStream)
		{
			Microsoft::WRL::ComPtr<IStream> pIStream;

			HRESULT hr = CreateStreamOverRandomAccessStream(
				reinterpret_cast<IUnknown*>(fileStream),
				IID_PPV_ARGS(&pIStream)
				);

			if (SUCCEEDED(hr))
			{
				hr = SetJPEGOrientationFlag(pIStream.Get(), 1U, pIWICImagingFactory);

				if (SUCCEEDED(hr))
				{
					auto moveAndReplaceAsyncTask = concurrency::create_task(tempFile->MoveAndReplaceAsync(originalFile));

					moveAndReplaceAsyncTask.then([]()
					{
						return S_OK;
					});
				}
			}
		});
	});
}

byte* GetPointerToByteData(Windows::Storage::Streams::IBuffer^ buffer)
{
	// Query the IBufferByteAccess interface.
	Microsoft::WRL::ComPtr<Windows::Storage::Streams::IBufferByteAccess> bufferByteAccess;
	reinterpret_cast<IInspectable*>(buffer)->QueryInterface(IID_PPV_ARGS(&bufferByteAccess));

	// Retrieve the buffer data.
	byte* pixels = nullptr;
	bufferByteAccess->Buffer(&pixels);
	return pixels;
}

byte* GetPointerToByteData(Windows::Storage::Streams::IBuffer^ buffer, unsigned int *length)
{
	if (length != nullptr)
	{
		*length = buffer->Length;
	}
	// Query the IBufferByteAccess interface.
	Microsoft::WRL::ComPtr<Windows::Storage::Streams::IBufferByteAccess> bufferByteAccess;
	reinterpret_cast<IInspectable*>(buffer)->QueryInterface(IID_PPV_ARGS(&bufferByteAccess));

	// Retrieve the buffer data.
	byte* pixels = nullptr;
	bufferByteAccess->Buffer(&pixels);
	return pixels;
}

concurrency::task<FILE *> StorageFileToFilePointer(Windows::Storage::StorageFile^ storageFile)
{
	FILE * filePointer = nullptr;

	return concurrency::create_task(Windows::Storage::FileIO::ReadBufferAsync(storageFile))
		.then([filePointer](Windows::Storage::Streams::IBuffer^ buffer) mutable
	{
		Windows::Storage::StorageFolder^ tempFolder = Windows::Storage::ApplicationData::Current->TemporaryFolder;

		if (nullptr != tempFolder)
		{
			HRESULT hr = S_OK;

			Platform::String^ tempFileName = tempFolder->Path + "\\" + GetUUID();

			CREATEFILE2_EXTENDED_PARAMETERS extendedParams = { 0 };
			extendedParams.dwSize = sizeof(CREATEFILE2_EXTENDED_PARAMETERS);
			extendedParams.dwFileAttributes = FILE_ATTRIBUTE_TEMPORARY;
			extendedParams.dwFileFlags = FILE_FLAG_DELETE_ON_CLOSE | FILE_FLAG_RANDOM_ACCESS;
			extendedParams.dwSecurityQosFlags = SECURITY_ANONYMOUS;
			extendedParams.lpSecurityAttributes = nullptr;
			extendedParams.hTemplateFile = nullptr;

			HANDLE tempFileHandle = CreateFile2(
				tempFileName->Data(),
				GENERIC_READ | GENERIC_WRITE | DELETE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				CREATE_ALWAYS,
				&extendedParams
				);

			if (INVALID_HANDLE_VALUE != tempFileHandle)
			{
				// Open the output file from the handle
				int fd = _open_osfhandle((intptr_t)tempFileHandle, _O_RDWR | _O_BINARY);

				if (-1 != fd)
				{
					_set_errno(0);

					filePointer = _fdopen(fd, "w+b");

					if (nullptr != filePointer)
					{
						if (buffer->Length == fwrite(GetPointerToByteData(buffer), sizeof(byte), buffer->Length, filePointer))
						{
							if (0 == fseek(filePointer, 0, SEEK_SET))
							{
								return filePointer;
							}
						}
					}
					else
					{
						wchar_t errorText[94] = { L'\0' };

						__wcserror_s(errorText, NULL);

						_close(fd); // Also calls CloseHandle()
					}
				}
				else
				{
					hr = TYPE_E_IOERROR;

					CloseHandle(tempFileHandle);
				}
			}
			else
			{
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
		}

		return filePointer;
	});
}

Scenario_AfterPick::Scenario_AfterPick()
{
    InitializeComponent();

	pIWICImagingFactory = nullptr;

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	if (FAILED(hr))
	{
		hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	}

	if (SUCCEEDED(hr))
	{
		CoInitializeExSucceeded = TRUE;

		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&pIWICImagingFactory)
			);

		//Windows::ApplicationModel::Package^ package = Windows::ApplicationModel::Package::Current;
		//Windows::Storage::StorageFolder^ installedLocation = package->InstalledLocation;
		//Windows::Storage::StorageFolder^ localFolder = Windows::Storage::ApplicationData::Current->LocalFolder;
		//Windows::Storage::StorageFolder^ temporaryFolder = Windows::Storage::ApplicationData::Current->TemporaryFolder;

		//DebugText->Text = "Installed location:\n" + installedLocation->Path + "\n" + "Local folder:\n" + localFolder->Path;
		//DebugText->Text = temporaryFolder->Path;
	}
	else
	{
		throw Platform::Exception::CreateException(hr);
	}
}

Scenario_AfterPick::~Scenario_AfterPick()
{
	if (pIWICImagingFactory)
	{
		pIWICImagingFactory->Release();
	}

	if (CoInitializeExSucceeded)
	{
		CoUninitialize();
	}
}

// <summary>
// Invoked when this page is about to be displayed in a Frame.
// </summary>
// <param name="e">Event data that describes how this page was reached. The Parameter
// property is typically used to configure the page.</param>
void Scenario_AfterPick::OnNavigatedTo(NavigationEventArgs^ e)
{
    // A pointer back to the main page.  This is needed if you want to call methods in MainPage such
    // as NotifyUser()
    rootPage = MainPage::Current;

	storeData = ref new Data();

	auto openPicker = ref new Windows::Storage::Pickers::FileOpenPicker();
	openPicker->SuggestedStartLocation = Windows::Storage::Pickers::PickerLocationId::PicturesLibrary;
	openPicker->ViewMode = Windows::Storage::Pickers::PickerViewMode::Thumbnail;

	// Filter to include a sample subset of file types.
	openPicker->FileTypeFilter->Clear();
	openPicker->FileTypeFilter->Append(".jpg");
	openPicker->FileTypeFilter->Append(".jpeg");
	openPicker->FileTypeFilter->Append(".jpe");
	openPicker->FileTypeFilter->Append(".jif");
	openPicker->FileTypeFilter->Append(".jfif");
	openPicker->FileTypeFilter->Append(".jfi");

	// All this work will be done asynchronously on a background thread:

	// Wrap the async call inside a concurrency::task object
	auto pickerTask = concurrency::create_task(openPicker->PickMultipleFilesAsync());

	// Accept the unwrapped return value of previous call as input param
	pickerTask.then([this](IVectorView<Windows::Storage::StorageFile^>^ files)
	{
		// file is null if user cancels the file picker.
		if (0 == files->Size)
		{
			// Stop work and clean up.
			concurrency::cancel_current_task();
		}

		GridView1->ItemsSource = storeData->Items;

		for (unsigned int i = 0U; i < files->Size; ++i)
		{
			Item^ item = ref new Item();

			item->Title = files->GetAt(i)->Name;

			// Add picked file to MostRecentlyUsedList.
			//mruToken = Windows::Storage::AccessCache::StorageApplicationPermissions::MostRecentlyUsedList->Add(files->GetAt(i));

			// Return the IRandomAccessStream^ object
			auto openingTask = concurrency::create_task(files->GetAt(i)->OpenAsync(Windows::Storage::FileAccessMode::Read));

			openingTask.then([this, files, i, item](Windows::Storage::Streams::IRandomAccessStream^ fileStream)
			{
				Microsoft::WRL::ComPtr<IStream> pIStream;

				HRESULT hr = CreateStreamOverRandomAccessStream(
					reinterpret_cast<IUnknown*>(fileStream),
					IID_PPV_ARGS(&pIStream)
					);

				if (SUCCEEDED(hr))
				{
					USHORT OrientationFlagValue = 0U;

					hr = GetJPEGOrientationFlag(pIStream.Get(), OrientationFlagValue, pIWICImagingFactory);

					if (SUCCEEDED(hr))
					{
						//safe_cast<Item^>(storeData->Items->GetAt(i))->Category = "Orientation flag: " + OrientationFlagValue.ToString();
						item->Category = "Orientation flag: " + OrientationFlagValue.ToString();

						/*if ((OrientationFlagValue >= 2U && OrientationFlagValue <= 8U))
						{
							auto op = StorageFileToFilePointer(files->GetAt(i));

							op.then([this, i, files, OrientationFlagValue](FILE * filePointer)
							{
								// fclose on filePointer is the responsibility of ChangeOrientation
								HRESULT hr = ChangeOrientation(files->GetAt(i), filePointer, OrientationFlagValue, pIWICImagingFactory, rootPage->TrimChecked, rootPage->ProgressiveChecked);
							});
						}*/
					}
					else
					{
						//safe_cast<Item^>(storeData->Items->GetAt(i))->Category = "No orientation flag";
						item->Category = "No orientation flag";
					}

					auto getThumbnailTask = concurrency::create_task(files->GetAt(i)->GetThumbnailAsync(Windows::Storage::FileProperties::ThumbnailMode::SingleItem));

					getThumbnailTask.then([this, i, files, OrientationFlagValue, item](Windows::Storage::FileProperties::StorageItemThumbnail^ thumbnail)
					{
						// Set the stream as source of the bitmap
						Windows::UI::Xaml::Media::Imaging::BitmapImage^ bitmapImage = ref new Windows::UI::Xaml::Media::Imaging::BitmapImage();
						bitmapImage->SetSource(thumbnail);

						// Set the bitmap as source of the Image control
						//safe_cast<Item^>(storeData->Items->GetAt(i))->Image = bitmapImage;
						item->Image = bitmapImage;

						storeData->Items->Append(item);
					});
				}
			});
		}
	});
}

// <summary>
// We will visualize the data item in asynchronously in multiple phases for improved panning user experience 
// of large lists.  In this sample scneario, we will visualize different parts of the data item
// in the following order:
// 
//     1) Placeholders (visualized synchronously - Phase 0)
//     2) Title (visualized asynchronously - Phase 1)
//     3) Category and Image (visualized asynchronously - Phase 2)
//
// </summary>
// <param name="sender"></param>
// <param name="args"></param>
void JPG_Spinner::Scenario_AfterPick::ItemGridView_ContainerContentChanging(
    ListViewBase^ sender,
    Windows::UI::Xaml::Controls::ContainerContentChangingEventArgs^ args)
{
    ItemViewer^ iv = safe_cast<ItemViewer^>(args->ItemContainer->ContentTemplateRoot);

    if (iv != nullptr)
    {
        // if the container is being added to the recycle queue (meaning it will not particiapte in 
        // visualizing data items for the time being), we clear out the data item
        if (args->InRecycleQueue == true)
        {
            iv->ClearData();
        }
        else if (args->Phase == 0)
        {
            iv->ShowPlaceholder(safe_cast<Item^>(args->Item));

            // Register for async callback to visualize Title asynchronously
            args->RegisterUpdateCallback(ContainerContentChangingDelegate);
        }
        else if (args->Phase == 1)
        {
            iv->ShowTitle();
            args->RegisterUpdateCallback(ContainerContentChangingDelegate);
        }
        else if (args->Phase == 2)
        {
            iv->ShowCategory();
            iv->ShowImage();
        }

        args->Handled = true;
    }
}