#ifndef _ALEMBIC_OBJECT_H_
#define _ALEMBIC_OBJECT_H_

#include "Foundation.h"
#include <xsi_ref.h>
#include <xsi_doublearray.h>
#include <vector>
#include <boost/exception/all.hpp>
#include "AlembicLicensing.h"
#include "AlembicMetaData.h"

class AlembicWriteJob;

class AlembicObject
{
private:
   XSI::CRefArray mRefs;
   AlembicWriteJob * mJob;
   Alembic::Abc::OObject mOParent;
protected:
   int mNumSamples;
   Alembic::AbcGeom::OVisibilityProperty mOVisibility;

public:
   AlembicObject(const XSI::CRef & in_Ref, AlembicWriteJob * in_Job);
   ~AlembicObject();

   AlembicWriteJob * GetJob() { return mJob; }
   const XSI::CRef & GetRef(ULONG index = 0) { return mRefs[index]; }
   ULONG GetRefCount() { return mRefs.GetCount(); }
   void AddRef(const XSI::CRef & in_Ref) { mRefs.Add(in_Ref); }
   Alembic::Abc::OObject GetOParent() { return mOParent; }
   virtual Alembic::Abc::OCompoundProperty GetCompound() = 0;
   int GetNumSamples() { return mNumSamples; }

   virtual XSI::CStatus Save(double time) = 0;
};

typedef boost::shared_ptr < AlembicObject > AlembicObjectPtr;

class alembic_UD
{
public:
   alembic_UD(ULONG in_id);
   ~alembic_UD();

   size_t lastFloor;
   double lastTime;

   std::vector<double> times;
   std::vector<Alembic::Abc::M44d> matrices;

   static void clearAll();

private:
   ULONG id;
   static std::map<ULONG,alembic_UD*> gAlembicUDs;

};

#include "AlembicWriteJob.h"

#endif